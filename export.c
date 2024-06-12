/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:39:39 by bruno             #+#    #+#             */
/*   Updated: 2024/06/12 10:32:28 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	swap_nodes(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->line;
	a->line = b->line;
	b->line = tmp;
}

t_env	*alphabetical_env(t_env *tmp)
{
	int 		swapped;
	t_env	*ordered;
	t_env	*current;

	if (!tmp)
		return (NULL);
	ordered = tmp;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = ordered;
		while (current->next)
		{
			if (ft_strcmp(current->line, current->next->line) > 0)
			{
				swap_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (ordered);
}

void	export_cmd(t_main *main, char **token)
{
	int		i;
	t_env 	*tmp;


	tmp = main->env;
	if (!token[1])
	{
		t_env *sorted_env = alphabetical_env(tmp);
		while (sorted_env)
		{
			printf("declare -x %s\n", sorted_env->line);
			sorted_env = sorted_env->next;
		}
	}
	i = 1;
	while (token[i])
	{
		if (!(ft_isalpha(token[i][0])))
		{
			printf("bash: export: '%s': not a valid identifier\n",token[i]);
			i++;
		}
		if (!token[i])
			break ;
		if (ft_strchr(token[i],'='))
			add_env(&main->env, token[i], 1);
		else
			add_env(&main->env, token[i], 0);
		i++;
	}
}
