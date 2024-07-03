/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:01:49 by jazevedo          #+#    #+#             */
/*   Updated: 2024/07/02 15:03:39 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	transfer_nodes(t_tokens *tokens, t_tokens *right)
{
	t_node	*node;
	t_node	*next;

	if (!tokens || !right)
		return ;
	node = right->first->next; //| Segundo node em diante.
	while (node)
	{
		next = node->next;
		//| Remover o node da lista right.
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		if (node == right->last)
			right->last = node->prev;
		//| Adicionar o node na lista tokens.
		node->next = NULL;
		node->prev = tokens->last;
		if (tokens->last)
			tokens->last->next = node;
		else
			tokens->first = node;
		tokens->last = node;
		right->size--;
		tokens->size++;
		node = next;
	}
	right->first->next = NULL;
	right->last = right->first;
	right->size = 1;
}

void	remove_last_node(t_tokens *tokens)
{
	t_node	*last;

	if (!tokens || !tokens->last)
		return ;
	last = tokens->last;
	if (tokens->last->prev) //| Se não tiver só um node.
		tokens->last->prev->next = NULL; //Substitui o último por NULL.
	tokens->last = tokens->last->prev; //O antepenúltimo será o novo último.
	if (!tokens->last) //| Caso só tivesse só um node na lista.
		tokens->first = NULL;
	free(last->cmd);
	last->cmd = NULL;
	free(last);
	last = NULL;
	tokens->size--; //| Pois removemos um node da lista.
}

void	addfront_popback(t_tokens *right, t_tokens *tokens)
{
	t_node	*to_move;

	if (!tokens || !tokens->last)
		return ;
	to_move = tokens->last;
	// Remover do final da tokens
	if (tokens->last->prev)
	{
		tokens->last = tokens->last->prev;
		tokens->last->next = NULL;
	}
	else
	{ // Se só tiver um node
		tokens->first = NULL;
		tokens->last = NULL;
	}
	// Adicionar o node na frente do right
	to_move->next = right->first;
	to_move->prev = NULL;
	if (right->first)
		right->first->prev = to_move;
	right->first = to_move;
	if (!right->last) // Se right estiver vazia
		right->last = to_move;
	tokens->size--;
	right->size++;
}

t_tokens	*split_tokens(t_tokens *tokens, t_node *node)
{
	t_node		*tmp;
	t_tokens	*right;

	if (!tokens || !node)
		return (NULL);
	right = start_tokens();
	tmp = tokens->last;
	while (tmp && tmp != node)
	{
		addfront_popback(right, tokens); //| Adicionar no começo e tirar do final.
		tmp = tokens->last;
	}
	return (right);
}
