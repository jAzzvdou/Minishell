/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:26 by bruno             #+#    #+#             */
/*   Updated: 2024/06/14 11:11:27 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_env **env, char *line,int declare_x)
{
	t_env *new;
	t_env *tmp;

	new = (t_env *)malloc(sizeof(t_env));
	new->declare_x = declare_x;
	new->name = ft_strndup(line, strchr(line, '=') - line);
	new->value = ft_strdup(strchr(line, '=') + 1);
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

void	start_env(t_main *main, char **envp)
{
	int     i;

	i = -1;
	while (envp[++i])
		add_env(&main->env, envp[i],1);
}

void	env_cmd(t_main *main, char **token)
{
	int	i;
	t_env	*env;

	i = 0;
	while (token[i])
	{
		if (!strcmp(token[i], "env"))
			i++;
		else
		{
			error_env(token[i]);
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
}
