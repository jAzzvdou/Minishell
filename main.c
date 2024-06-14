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
void	heredoc(t_main *main, char *limiter, int hd)//, int hd)
{
	char	*line;

	while (1)
	{
		line = readline(GREEN"> "WHITE);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(line)))
			break ;
		write(hd, line, ft_strlen(line));
		write(hd, "\n", 1);
		free(line);
	}
	//close(hd);
	free(line);
	free(limiter);
	printf(GREEN"heredoc done!\n");
	(void)main;
	// mandar para a pipex
}

int	start_heredoc(t_main *main, t_node *node)
{
	//int	hd[2];
	char	*limiter;

	main->fd[1] = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (main->fd[1] < 0)
		return (0);
	//pipe(hd);
	//main->fd[0] = hd[0];
	limiter = ft_strdup(node->cmd);
	heredoc(main, limiter, main->fd[0]);//hd[1]);
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
