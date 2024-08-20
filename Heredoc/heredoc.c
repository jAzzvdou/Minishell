/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/20 13:47:02 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	handle_loop_heredoc(t_loop_params *loop_params,
	t_heredoc_params *heredoc_params)
{
	signal(SIGINT, sig_int_heredoc_handle);
	while (1)
	{
		loop_params->line = readline(GREEN"> ");
		if (!loop_params->line)
		{
			err_heredoc(heredoc_params->token->cmd);
			free(loop_params->file);
			free_tokens2(heredoc_params->tokens);
			free_everything(heredoc_params->main);
			exit(1);
		}
		if (!ft_strcmp(heredoc_params->token->cmd, loop_params->line))
		{
			free(loop_params->line);
			free(loop_params->file);
			free_tokens2(heredoc_params->tokens);
			free_everything(heredoc_params->main);
			exit(0);
		}
		write(loop_params->fd, loop_params->line, strlen(loop_params->line));
		write(loop_params->fd, "\n", 1);
		free(loop_params->line);
	}
}

int	heredoc(t_heredoc_params *heredoc_params, char *file, int fd)
{
	int				status;
	pid_t			hd_pid;
	t_loop_params	loop_params;

	loop_params.line = NULL;
	loop_params.fd = fd;
	loop_params.file = file;
	signal(SIGINT, SIG_IGN);
	hd_pid = fork();
	if (hd_pid == -1)
		handle_err_fork_heredoc();
	if (hd_pid == 0)
		handle_loop_heredoc(&loop_params, heredoc_params);
	waitpid(hd_pid, &status, 0);
	g_status = WEXITSTATUS(status);
	if (g_status == 130)
	{
		handle_heredoc_interrupt(loop_params.file, loop_params.fd);
		return (-1);
	}
	close(fd);
	free(heredoc_params->token->cmd);
	heredoc_params->token->cmd = file;
	return (1);
}

int	start_heredoc(t_main *main, t_tokens *tokens, t_node *token, int nb)
{
	int					fd;
	static long int		random;
	char				*file;
	char				*tmp;
	t_heredoc_params	heredoc_params;

	random = random + (u_int64_t)start_heredoc * nb;
	file = free_function(ft_strdup("/tmp/heredoc"), ft_itoa(random));
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		free(file);
		return (0);
	}
	if (token->cmd[0] == '\'' || token->cmd[0] == '\"')
	{
		tmp = token->cmd;
		token->cmd = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
		free(tmp);
	}
	heredoc_params.tokens = tokens;
	heredoc_params.token = token;
	heredoc_params.main = main;
	return (heredoc(&heredoc_params, file, fd));
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
