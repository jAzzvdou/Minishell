/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:18 by bruno             #+#    #+#             */
/*   Updated: 2024/06/17 09:46:04 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	check_tokens(t_tokens *tokens)
{
	e_type	type;
	t_node	*first;
	t_node	*last;

	first = tokens->first;
	last = tokens->last;
	type = first->type;
	if (type == PIPE || type == OR || type == AND)
		return (error_syntax(tokens->first->cmd, 1));
	type = last->type;
	if (type == PIPE || type == OR || type == AND
		|| type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
		return (error_syntax(NULL, 2));
	while (first->next)
	{
		type = first->type;
		if (type == PIPE || type == OR || type == AND)
		{
			type = first->next->type;
			if (type == PIPE || type == OR || type == AND)
				return (error_syntax(first->next->cmd, 1));
		}
		else if (type == INPUT || type == OUTPUT
			|| type == HEREDOC || type == APPEND)
		{
			type = first->next->type;
			if (type == PIPE || type == OR || type == AND
				|| type == INPUT || type == OUTPUT
				|| type == HEREDOC || type == APPEND)
				return (error_syntax(first->next->cmd, 1));
		}
		first = first->next;
	}
	return (1);
}
