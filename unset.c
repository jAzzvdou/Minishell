/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:01:20 by bruno             #+#    #+#             */
/*   Updated: 2024/06/12 21:02:06 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->name);
		free(node->value);
		free(node->line);
		free(node);
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
				// Remove o nó da lista
				if (prev)
					prev->next = temp->next;
				else
					main->env = temp->next;

				// Libera a memória do nó removido
				free_env_node(temp);
				break;
			}

			prev = temp;
			temp = temp->next;
		}
		i++;
	}
}