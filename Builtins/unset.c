/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:01:20 by bruno             #+#    #+#             */
/*   Updated: 2024/06/18 13:04:28 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->name);
		node->name = NULL;
		free(node->value);
		node->value = NULL;
		free(node->line);
		node->line = NULL;
		free(node);
		node = NULL;
	}
}

void	unset_cmd(t_main *main, char **token)
{
	t_env	*temp;
	t_env	*prev;
	int		i;

	if (!token[1])
		return ;
	i = 1;
	while (token[i])
	{
		temp = main->env;
		prev = NULL;
		while (temp)
		{
			if (ft_strcmp(temp->name, token[i]) == 0)
			{
				if (prev)
					prev->next = temp->next;
				else
					main->env = temp->next;
				free_env_node(temp);
				break;
			}

			prev = temp;
			temp = temp->next;
		}
		i++;
	}
}
