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

void	parser(t_main *main, t_tokens *tokens)
{
	if (!tokens || !check_tokens(tokens))
		return ;
	main->tokens = tokens;
	if (!is_there_heredoc(main->tokens))
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
