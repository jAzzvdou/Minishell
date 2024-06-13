#include "minishell.h"

char	*user_input(void)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
		input = ft_strdup("exit");
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

//----------| HEREDOC |----------//
void	heredoc(t_main *main, char *limiter, int hd)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(line, limiter, ft_strlen(line)))
			break ;
		write(hd, line, ft_strlen(line));
		free(line);
	}
	close(hd);
	free(line);
	free(limiter);

	(void)main;
	printf(GREEN"heredoc done!\n");
	// mandar para a pipex
}

int	start_heredoc(t_main *main, t_node *node)
{
	int	fd[2];
	int	hd[2];
	char	*limiter;

	fd[1] = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (fd[1] < 0)
		return (0);
	pipe(hd);
	fd[0] = hd[0];
	limiter = ft_strjoin(node->cmd, "\n");
	heredoc(main, limiter, hd[1]);
	return (1);
}

int	is_there_heredoc(t_main *main, t_tokens *tokens)
{
	t_node	*token;

	token = tokens->first;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (!start_heredoc(main, token->next))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
//----------| ------- |----------//

void	parser(t_main *main, t_tokens *tokens)
{
	if (!tokens || !check_tokens(tokens))
		return ;
	main->tokens = tokens;
	if (!is_there_heredoc(main, main->tokens))
		return ;
	controller(main, main->tokens->first->cmd_args);
	//| Ver se tem algum Heredoc
	//| Construir a árvore.
	//| Executar a árvore.
}

int	main(int argc, char **argv, char **envp)
{
	t_main	main;

	(void)argv;
	if (argc != 1)
		return (error_argc());
	main = (t_main){0};
	start_env(&main, envp);
	start_pwd(&main);
	start_signals();
	while (1)
		parser(&main, tokenizator(user_input()));
	return (0);
}
