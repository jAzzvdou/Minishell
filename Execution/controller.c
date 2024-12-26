#include "../Include/minishell.h"

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
		args[i[0]] = my_strdup(node->line);
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
	while (env[i] && my_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	paths = my_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		aux = my_strjoin(paths[i], "/");
		path = my_strjoin(aux, cmd);
		free(aux);
		if (!access(path, F_OK | X_OK))
			return (path);
		free(path);
	}
	free_matrix(paths);
	return (NULL);
}

void	try_exec(t_main *main, char **env, char **tokens, char *cmd)
{
	char	*path;

	path = pathfinder(env, cmd);
	if (!path)
	{
		err(GREY"minichad: ");
		err(cmd);
		err(": command not found\n"WHITE);
		free(path);
		free_matrix(env);
		free_matrix(tokens);
		free_everything(main);
		exit(127);
	}
	if (execve(path, tokens, env) < 0)
		exit(127);
}

void	executer(t_main *main, char **tokens, char *cmd)
{
	int		status;
	char	**env;
	pid_t	pid;

	env = list_to_args(main->env);
	pid = fork();
	if (!pid)
	{
		if (!access(cmd, F_OK | X_OK))
		{
			if (execve(cmd, tokens, env) < 0)
				free_exit(main, env, tokens, cmd);
		}
		else
			try_exec(main, env, tokens, cmd);
	}
	free_matrix(env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	if ((!my_strcmp(cmd, "cat") || !my_strcmp(cmd, "grep")) && status == 2)
		status = 130;
	last_status(status);
}

void	controller(t_main *main, char **tokens)
{
	if (!builtins(main, tokens))
		executer(main, tokens, tokens[0]);
	free_matrix(tokens);
}
