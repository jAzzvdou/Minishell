#include "minishell.h"

char	*user_input(void)
{
	char	*input;

	input = readline(RED"m"ORANGE"i"YELLOW"n"GREEN"i"CYAN"s"BLUE
			"h"LILAC"e"PURPLE"l"PINK"l"GREY"$ "WHITE);
	if (!input)
		input = ft_strdup("exit");
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

void	parser(char *user_input)
{
	//| Criar uma lista de tokens.
	//| Checar a gramática desses tokens.
	//| Ver se tem algum Heredoc
	//| Construir a árvore.
	//| Executar a árvore.
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp; //| We will use ENV in the future.
	if (argc != 1)
		return (error_argc());

	//| Start Signals
	start_signals();
	//| -> Pegar o ENV.
	//| -> Fazer o 'pwd' com uma static.

	//| The While True
	while (1)
		parser(user_input()); //| PARSER: NOT CREATED.

	return (0);
}

/*
	BUILTINS:
- echo (with option '-n')
- cd
- pwd
- export
- unset
- env
- exit
*/
