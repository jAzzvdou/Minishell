/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/19 16:14:41 by jazevedo         ###   ########.fr       */
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

int	heredoc(t_main *main, t_tokens *tokens, t_node *token, char *file, int fd)
{
	int		status;
	pid_t	hd_pid;
	char	*line;

	signal(SIGINT, SIG_IGN);
	hd_pid = fork();
	if (hd_pid == -1)
	{
		err(RED"fork\n"RESET);
		return (-1);
	}
	if (hd_pid == 0)
	{
		signal(SIGINT, sig_int_heredoc_handle);
		while (1)
		{
			line = readline(GREEN"> ");
			if (!line)
			{
				err_heredoc(token->cmd);
				free(file);
				free_tokens2(tokens);
				free_everything(main);
				exit(1);
			}
			if (!ft_strcmp(token->cmd, line))
			{
				free(line);
				free(file);
				free_tokens2(tokens);
				free_everything(main);
				exit(0);
			}
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
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
	free(token->cmd);
	token->cmd = file;
	return (1);
}

int	start_heredoc(t_main *main, t_tokens *tokens, t_node *token, int nb)
{
	int				fd;
	static long int	random;
	char			*file;
	char			*tmp;

	random = random + (u_int64_t)start_heredoc * nb;
	file = free_function(ft_strdup("/tmp/heredoc"), ft_itoa(random));
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (free(file), 0);
	if (token->cmd[0] == '\'' || token->cmd[0] == '\"')
	{
		tmp = token->cmd;
		token->cmd = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
		free(tmp);
	}
	return (heredoc(main, tokens, token, file, fd));
}

int	is_there_heredoc(t_main *main, t_tokens *tokens)
{
	t_node	*token;

	token = tokens->first;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (!start_heredoc(main, tokens, token->next, 42))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
