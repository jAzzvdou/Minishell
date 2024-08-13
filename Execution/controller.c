/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:49 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/13 14:26:25 by btaveira         ###   ########.fr       */
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
	char	**env;
	pid_t	pid;

	env = list_to_args(main->env);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		handle_child_process(main, cmd, tokens, env);
		free_matrix(env);
	}
	else
	{
		handle_parent_process(pid, &status);
	}
	free_matrix(env);
}

void	controller(t_main *main, char **tokens)
{
	if (!builtins(main, tokens))
		executer(main, tokens, tokens[0]);
	free_matrix(tokens);
}
