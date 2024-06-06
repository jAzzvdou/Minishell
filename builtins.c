#include "minishell.h"

void	env_cmd(char **token)
{
	int	i;
	char	**env;

	i = 0;
	while (token[i])
	{
		if (!strcmp(token[i], "env"))
			i++;
		else
		{
			printf(GREY"env: '%s': No such file or directory\n",
				token[i]);
			return ;
		}
	}
	env = static_env(NULL, NOFREE);
	i = -1;
	while (env[++i])
		printf(WHITE"%s\n"RESET, env[i]);
}

void	exit_cmd(char **token)
{
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
	{
		static_env(NULL, FREE);
		static_pwd(NULL, FREE);
		printf(ORANGE"exit\n"RESET);
		printf(GREY"bash: exit: %s: numeric argument required\n"RESET,
			token[1]);
		exit(1);
	}
	if (token[1] && token[2])
	{
		static_env(NULL, FREE);
		static_pwd(NULL, FREE);
		printf(ORANGE"exit\n"RESET);
		printf(GREY"bash: exit: too many arguments\n"RESET);
		exit(1);
	}
	static_env(NULL, FREE);
	static_pwd(NULL, FREE);
	printf(ORANGE"exit\n"RESET);
	exit(1);
}

void	pwd_cmd(void)
{
	char	*pwd;

	pwd = static_pwd(NULL, NOFREE);
	printf("%s\n", pwd);
}

int	check_flag(char *token)
{
	if (token && !ft_strcmp(token, "-n"))
		return (1);
	return (0);
}

void	echo_cmd(char **token)
{
	int	i;
	int	space;
	int	newline;

	i = 1;
	newline = 1;
	while (check_flag(token[i]))
	{
		i++;
		newline = 0;
	}
	space = 0;
	while (token[i])
	{
		if (space)
			printf(" ");
		else
			space++;
		printf("%s", token[i++]);
	}
	if (newline)
		printf("\n");
}

void	export_cmd(char **token)
{
	if (!token[1])
		printf("declare x - ENV.\n"); //declare_x(); Função para printar o env.
	else
		printf("OK. Ainda tem que verificar a gramática.\n");
	//| Não pode começar com números e nem símbolos.
	//| Pode funcionar sem o '=' depois do nome do export, mas não vai adicionar no env, mas entra no 'declare x'.
}

void	controller(char **token)
{
	if (!strcmp(token[0], "exit"))
		exit_cmd(token);
	else if (!strcmp(token[0], "env")) //| Colocar o env em uma lista(??)
		env_cmd(token);
	else if (!strcmp(token[0], "pwd"))
		pwd_cmd();
	else if (!strcmp(token[0], "echo"))
		echo_cmd(token); //| LEMBRAR DE TRATAR '$0' E '$$'.
	else if (!strcmp(token[0], "export"))
		export_cmd(token);
	/*else if (!strcmp(token[0], "unset"))
		unset_cmd(token);
	else if (!strcmp(token[0], "cd"))
		cd_cmd(token);*/
}
