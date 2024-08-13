/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:58 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/13 17:44:57 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	check_start(t_node *first)
{
	t_type	type;

	type = first->type;
	if (type == PIPE || type == OR || type == AND)
		return (error_syntax(first->cmd, 1));
	return (0);
}

static int	check_end(t_node *last)
{
	t_type	type;

	type = last->type;
	if (type == PIPE || type == OR || type == AND ||
		type == INPUT || type == OUTPUT ||
		type == APPEND || type == HEREDOC)
		return (error_syntax(NULL, 2));
	return (0);
}

static int	check_consecutive(t_node *node)
{
	t_type	type;
	t_type	next_type;

	type = node->type;
	next_type = node->next->type;
	if ((type == PIPE || type == OR || type == AND) &&
		(next_type == PIPE || next_type == OR || next_type == AND))
		return (error_syntax(node->next->cmd, 1));
	if ((type == INPUT || type == OUTPUT || type == HEREDOC || type == APPEND) &&
		(next_type == PIPE || next_type == OR || next_type == AND ||
		 next_type == INPUT || next_type == OUTPUT || next_type == HEREDOC || next_type == APPEND))
		return (error_syntax(node->next->cmd, 1));
	return (0);
}

int	check_tokens(t_tokens *tokens)
{
	t_node	*first;
	t_node	*last;

	first = tokens->first;
	last = tokens->last;
	if (check_start(first) || check_end(last))
		return (0);
	while (first->next)
	{
		if (check_consecutive(first))
			return (0);
		first = first->next;
	}
	return (1);
}
