/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:40:07 by jazevedo          #+#    #+#             */
/*   Updated: 2024/07/08 16:59:28 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	make_if(t_main *main, t_tree *tree)
{
	if (tree->type == AND)
	{
		if (tree->left)
			exec(main, tree->left);
		if (last_status(-1) == 0 && tree->right)
			exec(main, tree->right);
	}
	else if (tree->type == OR)
	{
		if (tree->left)
			exec(main, tree->left);
		if (last_status(-1) != 0 && tree->right)
			exec(main, tree->right);
	}
}
/*
void	make_pipe(t_tree *pipe)
{
	int	fd[2];
	pid_t	pid[2];

	if (pipe[fd])
		last_status(1);
	//| Fazer os pipes.
	//| Lembrar de fechar os fds e o pipe certinho e dar free no que precisar.
}
*/

int	env_size(t_env *env)
{
	int	count;
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
	int	i;
	int	size;
	char	**args;
	t_env	*node;

	size = env_size(env);
	if (!size)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	node = env;
	i = 0;
	int ii = -1;
	while (++ii < size)
	{
		args[i] = ft_strdup(node->line);
		if (!args[i])
		{
			while (i > 0)
			{
				free(args[--i]);
				args[i] = NULL;
			}
			free(args);
			args = NULL;
			return (NULL);
		}
		i++;
		node = node->next;
	}
	args[i] = NULL;
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
	int	status;
	char	*path;
	char	**env;
	pid_t	pid;

	env = list_to_args(main->env);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		//| Verificar se é relative path.
		if (!access(cmd, F_OK | X_OK)) //| Se for já manda pro comando.
		{
			if (execve(cmd, tokens, env) < 0)
				exit(1);
		}
		else //| Se não for tem que procurar o Path dele se existir
		{
			path = pathfinder(env, cmd); //| Já tenho essa função também, na pipex.
			if (!path)
			{
				err(GREY"minichad: ");
				err(cmd);
				err(": command not found\n"WHITE);
				exit(1);
			}
			if (execve(path, tokens, env) < 0)
				exit(1);
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

void	re_exec(t_main *main, char *block)
{
	int	status;
	char	*new_input;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		new_input = ft_strndup(block + 1, ft_strlen(block) - 2);
		free(block);
		block = NULL;
		parser(main, tokenizator(new_input));
		free_everything(main);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	last_status(status);
}

void	controller(t_main *main, char **tokens)
{
	last_status(0);
	if (!builtins(main, tokens)) //| Se não for builtin.
		executer(main, tokens, tokens[0]);
	//if (g_status == SIGINT)
	//	last_status(130);
	free_matrix(tokens);
}

void	exec(t_main *main, t_tree *tree)
{
	if (tree->type == AND || tree->type == OR)
		make_if(main, tree);
	/*else if (tree->type == PIPE)
		//make_pipe(main, tree); //| LIDAR COM ISSO (FAZER A PIPEX);
	else if (tree->type == INPUT || tree->type == OUTPUT
		|| tree->type == HEREDOC || tree->type == APPEND)
		//make_redir(); //| LIDAR COM ISSO (FAZER OS REDIRECTS);*/
	else if (tree->left)
		exec(main, tree->left);
	else if (tree->right)
		exec(main, tree->right);
	else if (tree->exe && tree->exe->first)
	{
		if (tree->type == BLOCK)
			re_exec(main, tree->exe->first->cmd); //| LIDAR COM ISSO;
		else
			controller(main, token_to_args(tree->exe)); //| LEAK NA TREE->EXE
	}
}
