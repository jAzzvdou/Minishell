/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:22:16 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/13 16:25:36 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	remove_node_from_right(t_node *node, t_tokens *right)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node == right->last)
		right->last = node->prev;
	right->size--;
}

void	add_node_to_tokens(t_node *node, t_tokens *tokens)
{
	node->next = NULL;
	node->prev = tokens->last;
	if (tokens->last)
		tokens->last->next = node;
	else
		tokens->first = node;
	tokens->last = node;
	tokens->size++;
}
