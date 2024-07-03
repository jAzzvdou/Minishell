/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:05:19 by bruno             #+#    #+#             */
/*   Updated: 2024/07/03 15:28:22 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minishell.h"

int	handle_home(t_main *main)
{
	char	*path;

	path = env_value(main->env, "HOME");
	if (!path)
	{
		err(GREY"cd: HOME is not set\n"RESET);
		return (1);
	}
	if (chdir(path))
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	handle_tilde(t_main *main, char *token)
{
	int		ret;
	char	*path;
	char	*new_path;

	path = env_value(main->env, "HOME");
	if (!path)
	{
		err(GREY"cd: HOME is not set\n"RESET);
		return (1);
	}
	new_path = ft_strjoin(path, (token + 1)); //| Malloc
	if (!new_path)
	{
		err(GREY"cd: memory allocation error\n"RESET);
		return (1);
	}
	ret = chdir(new_path);
	if (ret)
	{
		err(GREY"minishell: cd"RESET);
		free(new_path);
		new_path = NULL;
		return (1);
	}
	free(new_path);
	new_path = NULL;
	return (0);
}

int	handle_oldpwd(t_main *main)
{
	char	*path;

	path = env_value(main->env, "OLDPWD");
	if (!path)
	{
		err(GREY"cd: OLDPWD is not set\n"RESET);
		return (1);
	}
	if (chdir(path))
	{
		err(GREY"minishell: cd 111"RESET);
		return (1);
	}
	printf("%s\n", path);
	return (0);
}

int	handle_path(char *path)
{
	if (chdir(path))
	{
		err(GREY"minishell: cd: "); //erro = 2
		err(path);
		err(": No such file or directory\n"RESET);
		return (1);
	}
	return (0);
}

void	update_pwd_oldpwd(t_main *main)
{
	char	new_pwd[4096];

	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		err(GREY"getcwd"RESET);
		return ;
	}
	free(main->old_pwd);
	main->old_pwd = main->pwd;
	main->pwd = strdup(new_pwd);
	update_env(&main->env, "OLDPWD", main->old_pwd);
	update_env(&main->env, "PWD", main->pwd);
}
