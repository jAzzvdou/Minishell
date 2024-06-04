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
//----------| TESTES |----------//
char *skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
	return (*str);
}
//----------|--------|----------//
void	parser(char *user_input)
{
	//(void)user_input;
	char	**token;

	skip_spaces(&user_input);
	if (!*user_input)
		return ;
	token = spliter(user_input);
	controller(token); //| PROVISÓRIO.
	//| Criar uma lista de tokens.
	//| Checar a gramática desses tokens.
	//| Ver se tem algum Heredoc
	//| Construir a árvore.
	//| Executar a árvore.
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (error_argc());

	//| Start Signals
	start_signals();
	
	start_env(envp); //| Para pegar o ENV atual, só chamar 'static_env(NULL, NOFREE);'
	start_pwd();//| -> Fazer o 'pwd' com uma static. Para sempre saber aonde estamos.

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
- env -> Já dá pra fazer esse porque já temos o ENV estático.
- exit
*/
