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
static int	skip_quotes(const char **s)
{
	char	quote;

	if (**s == '\'' || **s == '"')
		quote = **s;
	else
		return (0);
	(*s)++;
	while (**s && **s != quote)
		(*s)++;
	if (**s)
		(*s)++;
	return (1);
}

int	parenthesis_validation(const char *s)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (*s)
	{
		if (*s == '(')
			left++;
		else if (*s == ')')
			right++;
		if (right > left)
			break ;
		if (!skip_quotes(&s))
			s++;
	}
	if (right == left)
		return (1);
	return (0);
}
//----------|--------|----------//
t_list	tokenizator(char *user_input)
{
	t_list	tokens;

	tokens = (t_list){0};
	skip_spaces(&user_input);
	if (!*user_input)
		return (NULL);
	//| Validar as aspas (Para ver se elas estão fechadas corretamente).
	//| E validar os parêntesis (A gente já tinha feito, é o is_balanced()).
	if (!closed_quotes(user_input) || !close_parenthesis(user_input))
	{
		printf(RED"Error!\n"GREY"\tMinishell Only Parses Closed Quotes/Parenthesis.\n");
	}
	//| Static para a lista (assim como no env e pwd).
	//| Popular a lista. (???)
	return (tokens);
}

void	parser(t_list *tokens)
{
	(void)list;
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
		parser(tokenizator(user_input())); //| PARSER: NOT CREATED.

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
