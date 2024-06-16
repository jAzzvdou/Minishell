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

int	heredoc(t_node *token, char *file, int fd)
{
	const int	std_in = dup(STDIN_FILENO);
	char		*line;

	while (1)
	{
		line = readline(GREEN"> ");
		if (!line)
			break ;
		if (!ft_strcmp(token->cmd, line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	close(fd);
	close(std_in);
	free(token->cmd);
	token->cmd = file;
	printf("heredoc: %s\n", token->cmd);
	return (1);
}

int	start_heredoc(t_node *token, int nb)
{
	int		fd;
	static long int	random;
	char	*file;

	random = random + (u_int64_t)start_heredoc * nb;
	file = free_function(ft_strdup("/tmp/heredoc"), ft_itoa(random));
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (free(file), 0);
	return (heredoc(token, file, fd));
}

int     is_there_heredoc(t_tokens *tokens)
{
        t_node  *token;

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
