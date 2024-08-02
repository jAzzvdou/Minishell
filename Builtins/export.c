/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:39:39 by bruno             #+#    #+#             */
/*   Updated: 2024/08/02 10:50:06 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	swap_nodes(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->line;
	a->line = b->line;
	b->line = tmp;
}

t_env	*alphabetical_env(t_env *tmp)
{
	int			swapped;
	t_env		*ordered;
	t_env		*current;

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

void	add_without_equal(t_env **env, char *line, int declare_x)
{
	t_env	*new;
	t_env	*tmp;

	if (!line)
		return ;
	new = (t_env *)malloc(sizeof(t_env));
	new->declare_x = declare_x;
	new->name = ft_strdup(line);
	new->value = NULL;
	new->line = ft_strdup(line);
	new->next = NULL;
	if (!(*env))
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	export_cmd(t_main *main, char **token)
{
	int	i;

	if (!token[1])
	{
		handle_no_args(main->env);
		return ;
	}
	i = 1;
	while (token[i])
	{
		if (!is_valid_identifier(token[i]))
		{
			err(GREY"minichad: export: '");
			err(token[i]);
			err("': not a valid identifier\n"RESET);
			last_status(1);
			i++;
			continue ;
		}
		handle_equal_sign(main, token[i]);
		i++;
	}
}
