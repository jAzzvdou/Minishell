/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:20:17 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 17:20:19 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	add_env(t_env **env, char *line, int declare_x)
{
	char	*join;
	t_env	*new;
	t_env	*tmp;

	if (!line)
		return ;
	new = (t_env *)malloc(sizeof(t_env));
	new->declare_x = declare_x;
	new->name = ft_strndup(line, ft_strchr(line, '=') - line);
	if (!ft_strcmp(new->name, "SHLVL"))
	{
		new->value = ft_itoa(ft_atoll(ft_strchr(line, '=') + 1) + 1);
		join = ft_strndup(line, ft_strchr(line, '=') - line + 1);
		new->line = ft_strjoin(join, new->value);
		free(join);
	}
	else
	{
		new->value = ft_strdup(ft_strchr(line, '=') + 1);
		new->line = ft_strdup(line);
	}
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

void	start_env(t_main *main, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		add_env(&main->env, envp[i], 1);
}

void	env_cmd(t_main *main, char **token)
{
	int		i;
	t_env	*env;

	i = 0;
	while (token[i])
	{
		if (!ft_strcmp(token[i], "env"))
			i++;
		else
		{
			error_env(token[i]);
			last_status(127);
			return ;
		}
	}
	env = main->env;
	while (env)
	{
		if (env->declare_x)
			printf(WHITE"%s\n"RESET, env->line);
		env = env->next;
	}
	last_status(0);
}
