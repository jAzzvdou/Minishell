/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:41:22 by bruno             #+#    #+#             */
/*   Updated: 2024/06/24 14:19:44 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*free_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

char	*env_value(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_env **env, char *name, char *value)
{
	char	*line;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			free(tmp->line);
			tmp->line = ft_strjoin(name, "=");
			tmp->line = free_join(tmp->line, value);
			return ;
		}
		tmp = tmp->next;
	}
	line = ft_strjoin(name, "=");
	line = free_join(line, value);
	add_env(env, line, 1);
	free(line);
	line = NULL;
}

int	cd_cmd(t_main *main, char **token) 
{
	if (token[1] && token[2])
		return (err(GREY"cd: too many arguments\n"RESET), 1);
	if (!token[1] || token[1][0] == '\0' || !ft_strcmp(token[1], "~"))
	{
		if (handle_home(main)) 
			return (1);
	}
	else if (token[1][0] == '~')
	{
		if (handle_tilde(main, token[1])) 
			return (1);
	}
	else if (!ft_strcmp(token[1], "-"))
	{
		if (handle_oldpwd(main)) 
			return (1);
	}
	else
	{
		if (handle_path(token[1])) 
			return (1);
	}
	update_pwd_oldpwd(main);
	return (0);
}
