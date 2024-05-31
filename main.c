#include "minishell.h"

void	free_matrix(char ***matrix)
{
	int	i;

	//| Caso não tenha matrix, só retorna.
	if (!*matrix)
		return ;
	i = -1;
	while ((*matrix)[++i])
	{
		free((*matrix)[i]); //| Free direto no endereço.
		(*matrix)[i] = NULL;//| Setando para NULL para não ter double free.
	}
	free(*matrix); //| Libera a matrix.
	*matrix = NULL;
}

char	**static_env(char **new_envp, int clear)
{
	//| Static para poder acessar em outras partes do programa.
	static char	**env;

	//| Caso tenha um novo ENV, limpa o antigo.
	if (new_envp && env)
		free_matrix(&env);
	//| Atualiza o antigo ENV para o novo.
	if (new_envp)
		env = new_envp;
	//| Caso precise limpar o ENV.
	if (env && clear)
		free_matrix(&env);
	return (env);
}

void	start_env(char **envp)
{
	int	i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		new_env[i] = ft_strdup(envp[i]);
	new_env[i] = NULL;
	static_env(new_envp, NOFREE);
}

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
	start_env(envp); //| Para pegar o ENV atual, só chamar 'static_env(NULL, NOFREE);'
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
