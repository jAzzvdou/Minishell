#include "../Include/minishell.h"

char	*free_function(char *s1, char *s2)
{
	char	*tmp;

	tmp = my_strjoin(s1, s2);
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
	err("')\n"WHITE);
	last_status(0);
}

int	heredoc(t_node *token, char *file, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(GREEN"> ");
		if (!line)
		{
			err_heredoc(token->cmd);
			free(line);
			break ;
		}
		if (!my_strcmp(token->cmd, line))
		{
			free(line);
			last_status(0);
			break ;
		}
		write(fd, line, my_strlen(line));
		write(fd, "\n", 1);
		free_var(line);
	}
	close(fd);
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
	file = free_function(my_strdup("/tmp/heredoc"), my_itoa(random));
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (free(file), 0);
	if (token->cmd[0] == '\'' || token->cmd[0] == '\"')
	{
		tmp = token->cmd;
		token->cmd = my_strndup(tmp + 1, my_strlen(tmp) - 2);
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
