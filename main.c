#include "minishell.h"

char	*user_input(void)
{
	char	*input;

	input = readline(RED"m"ORANGE"i"YELLOW"n"GREEN"i"CYAN"s"BLUE
			"h"LILAC"e"PURPLE"l"BROWN"l"GREY"$ "WHITE);
	if (!input)
		input = ft_strdup("exit");
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

t_tokens	tokenizator(char *user_input)
{
	t_tokens	tokens;

	tokens = (t_tokens){0};
	skip_spaces(&user_input);
	if (!*user_input)
		return (NULL);
	if (!closed_quotes(user_input) || !closed_parenthesis(user_input))
	{
		printf(RED"Error!\n");
		printf(GREY"\tMinishell Only Parses Closed Quotes/Parenthesis.\n");
	}
	static_list(NULL, NOFREE);
	//| Popular a lista. (???)
	return (tokens);
}

void	parser(t_tokens *tokens)
{
	(void)tokens;
	//| Checar a gramática desses tokens.
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
	start_signals();
	start_pwd();
	while (1)
		parser(tokenizator(user_input())); //| PARSER: NOT CREATED.
	return (0);
}
