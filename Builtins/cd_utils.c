/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:05:19 by bruno             #+#    #+#             */
/*   Updated: 2024/06/18 12:21:34 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minishell.h"

int	handle_home(t_main *main)
{
	char	*path;

	path = env_value(main->env, "HOME");
	if (path == NULL)
	{
		printf("cd: HOME is not set\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int handle_tilde(t_main *main, char *token)
{
	int		ret;
	char	*path;
	char	*new_path;

	path = env_value(main->env, "HOME");
	if (path == NULL)
	{
		printf("cd: HOME is not set\n");
		return (1);
	}
	new_path = ft_strjoin(path, (token + 1));
	if (new_path == NULL)
	{
		printf("cd: memory allocation error\n");
		return (1);
	}
	ret = chdir(new_path);
	if (ret != 0)
	{
		perror("minishell: cd");
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

int	handle_oldpwd(t_main *main)
{
	char	*path;

	path = env_value(main->env, "OLDPWD");
	if (path == NULL)
	{
		printf("cd: OLDPWD is not set\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	printf("%s\n", path);
	return (0);
}

int	handle_path(char *path)
{
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

void update_pwd_oldpwd(t_main *main)
{
	char	new_pwd[1024];

	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("getcwd");
		return;
	}
	free(main->old_pwd);
	main->old_pwd = main->pwd;
	main->pwd = strdup(new_pwd);
	update_env(&main->env, "OLDPWD", main->old_pwd);
	update_env(&main->env, "PWD", main->pwd);
}
