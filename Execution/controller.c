/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:39:29 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/08 16:07:47 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	env_size(t_env *env)
{
	int		count;
	t_env	*list;

	list = env;
	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

char	**list_to_args(t_env *env)
{
	int		size;
	int		i[2];
	char	**args;
	t_env	*node;

	size = env_size(env);
	if (!size)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	node = env;
	i[0] = 0;
	i[1] = -1;
	while (++i[1] < size)
	{
		args[i[0]] = ft_strdup(node->line);
		if (!args[i[0]])
			return (free_args(args, i[0]), NULL);
		i[0]++;
		node = node->next;
	}
	args[i[0]] = NULL;
	return (args);
}

char	*pathfinder(char **env, char *cmd)
{
	int		i;
	char	*aux;
	char	*path;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		aux = ft_strjoin(paths[i], "/");
		path = ft_strjoin(aux, cmd);
		free(aux);
		if (!access(path, F_OK | X_OK))
			return (path);
		free(path);
	}
	free_matrix(paths);
	return (NULL);
}

void	executer(t_main *main, char **tokens, char *cmd)
{
	int		status;
	char	*path;
	char	**env;
	pid_t	pid;

	env = list_to_args(main->env);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		if (!access(cmd, F_OK | X_OK))
		{
			if (execve(cmd, tokens, env) < 0)
				exit(127);
		}
		else
		{
			path = pathfinder(env, cmd);
			if (!path)
			{
				err(GREY"minichad: ");
				err(cmd);
				err(": command not found\n"WHITE);
				exit(127);
			}
			if (execve(path, tokens, env) < 0)
				exit(127);
		}
	}
	free_matrix(env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	last_status(status);
}

void	controller(t_main *main, char **tokens)
{
	if (!builtins(main, tokens))
		executer(main, tokens, tokens[0]);
	free_matrix(tokens);
}
