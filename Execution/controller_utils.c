/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:21:05 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/13 14:35:52 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exec_cmd_directly(char *cmd, char **tokens, char **env)
{
	if (!access(cmd, F_OK | X_OK))
	{
		if (execve(cmd, tokens, env) < 0)
			exit(127);
	}
}

void	exec_cmd_pathfinder(t_main *main, char *cmd, char **tokens, char **env)
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

void	handle_child_process(t_main *main, char *cmd, char **tokens, char **env)
{
	if (fork() == 0)
	{
		exec_cmd_directly(cmd, tokens, env);
		exec_cmd_pathfinder(main, cmd, tokens, env);
	}
}

void	handle_parent_process(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	if (*status == 139)
		*status = 1;
	last_status(*status);
}
