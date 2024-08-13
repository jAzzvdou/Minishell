/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/13 15:49:03 by btaveira         ###   ########.fr       */
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

int	heredoc(t_node *token, char *file, int fd)
{
	int	result;

	signal(SIGINT, SIG_IGN);
	result = fork_and_handle_heredoc(token, file, fd);
	if (result == -1)
		return (-1);
	free(token->cmd);
	token->cmd = file;
	return (1);
}

int	start_heredoc(t_node *token, int nb)
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
	return (heredoc(token, file, fd));
}

int	is_there_heredoc(t_tokens *tokens)
{
	t_node	*token;

	token = tokens->first;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (!start_heredoc(token->next, 42))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
