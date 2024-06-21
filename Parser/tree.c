/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:39 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/21 17:02:29 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

//| Procurar por ANDs e ORs.
t_node	*is_type1(t_node *last)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

//| Procurar por PIPEs.
t_node  *is_type2(t_node *last)
{
        t_node  *tmp;

        tmp = last;
        while (tmp)
        {
                if (tmp->type == PIPE)
                        return (tmp);
                tmp = tmp->prev;
        }
        return (NULL);
}

//| Procurar por REDIRs.
t_node  *is_type3(t_node *last)
{
        t_node  *tmp;

        tmp = last;
        while (tmp)
        {
                if (tmp->type == INPUT || tmp->type == OUTPUT
			|| tmp->type == APPEND || tmp->type == HEREDOC)
                        return (tmp);
                tmp = tmp->prev;
        }
        return (NULL);
}

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
	t_node *to_move;

	if (!tokens || !tokens->last)
		return;
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

//| Estamos lendo os tokens de trás para frente.
int	make_roots(t_tree *tree, t_tokens *tokens, t_node *node)
{
	t_tokens	*right; // vai ser toda a parte da direita do node.

	if (!tree || !tokens || !node)
		return (0);
	right = split_tokens(tokens, node); //| Função que vai splitar o tokens em esquerda e direita.
					    //| A função vai retornar a parte da direita do node.
	if (!right)
		return (-1);
	tree->type = tokens->last->type; //| O tipo do node vai ser o tipo do último token.
					 //| (AND, OR, PIPE, REDIR ou CMD)
	//| Aqui a gente tem que tirar esse último node da lista de tokens.
	remove_last_node(tokens);
	//| Se o tipo do tree->type for um REDIR, a gente tem que fazer um tratamento especial.
	if (tree->type == INPUT || tree->type == OUTPUT
		|| tree->type == APPEND || tree->type == HEREDOC)
		transfer_nodes(tokens, right); //| Vamos lidar com isso: echo A > B C D E
					       //| Deve virar isso: echo A C D E > B.
	tree->left = build_tree(tokens);
	tree->right = build_tree(right);
	return (1);
}

//| Função que vai criar os nodes do tree com base na prioridade dos tokens.
void	search_priority(t_tree *tree, t_tokens *tokens)
{
	if (make_roots(tree, tokens, is_type1(tokens->last)))
		return ;
	if (make_roots(tree, tokens, is_type2(tokens->last)))
		return ;
	if (make_roots(tree, tokens, is_type3(tokens->last)))
		return ;
	tree->type = CMD;
	tree->exe = tokens;
}

t_tree	*start_tree(void)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->exe = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_tree	*build_tree(t_tokens *tokens)
{
	t_tree	*tree;

	tree = start_tree();
	if (!tree)
		return (NULL);
	search_priority(tree, tokens);
	return (tree);
}
