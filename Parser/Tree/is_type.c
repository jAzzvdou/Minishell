/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:23:55 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 17:24:04 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

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

t_node	*is_type2(t_node *last)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_node	*is_type3(t_node *last)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == OUTPUT \
		|| tmp->type == APPEND || tmp->type == HEREDOC)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
