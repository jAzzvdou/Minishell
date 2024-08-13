/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:48:03 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/13 15:50:43 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	err_heredoc(char *cmd)
{
	err(GREY"minichad: warning: here-document");
	err("at line N delimited by end-of-file (wanted `");
	err(cmd);
	err("')\n"RESET);
	last_status(0);
}

void	handle_heredoc_child_process(t_node *token, int fd)
{
	char	*line;

	signal(SIGINT, sig_int_heredoc_handle);
	while (1)
	{
		line = readline(GREEN"> ");
		if (!line)
		{
			err_heredoc(token->cmd);
			exit(1);
		}
		if (!ft_strcmp(token->cmd, line))
		{
			free(line);
			exit(0);
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc_parent_process(pid_t hd_pid, char *file, int fd)
{
	int		status;

	waitpid(hd_pid, &status, 0);
	g_status = WEXITSTATUS(status);
	if (g_status == 130)
	{
		unlink(file);
		close(fd);
		printf("\n");
		return (-1);
	}
	close(fd);
	return (1);
}

int	fork_and_handle_heredoc(t_node *token, char *file, int fd)
{
	pid_t	hd_pid;

	hd_pid = fork();
	if (hd_pid == -1)
	{
		err(RED"fork\n"RESET);
		return (-1);
	}
	if (hd_pid == 0)
		handle_heredoc_child_process(token, fd);
	else
		return (handle_heredoc_parent_process(hd_pid, file, fd));
	return (1);
}
