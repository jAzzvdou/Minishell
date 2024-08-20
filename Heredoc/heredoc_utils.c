/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:45:06 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/20 13:46:12 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*free_function(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (tmp);
}

void	err_heredoc(char *cmd)
{
	err(GREY"minichad: warning: here-document");
	err("at line N delimited by end-of-file (wanted `");
	err(cmd);
	err("')\n"RESET);
	last_status(0);
}

void	sig_int_heredoc_handle(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		g_status = 130;
		exit(g_status);
	}
	else
	{
		write(1, "> ", 2);
		ioctl(1, TIOCSTI, 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

int	handle_err_fork_heredoc(void)
{
	err(RED"fork\n"RESET);
	return (-1);
}

void	handle_heredoc_interrupt(char *file, int fd)
{
	unlink(file);
	close(fd);
	printf("\n");
}
