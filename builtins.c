#include "minishell.h"

void	env_cmd(char **token)
{
	int	i;
	char	**env;

	if (token[1])
	{
		//| Tem que dar erro porque ENV não aceita nenhuma flag.
		printf(RED"Error!\n"YELLOW"\tenv does not accept flags.\n"RESET);
		return ;
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
	if (!ft_strcmp(token, "-n"))
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

void	controller(char **token)
{
	if (!strcmp(token[0], "exit"))
		exit_cmd(token);
	else if (!strcmp(token[0], "env"))
		env_cmd(token);
	else if (!strcmp(token[0], "pwd"))
		pwd_cmd();
	else if (!strcmp(token[0], "echo"))
		echo_cmd(token);
	/*else if (!strcmp(token[0], "cd"))
		cd_cmd(token);
	else if (!strcmp(token[0], "export"))
		export_cmd(token);
	else if (!strcmp(token[0], "unset"))
		unset_cmd(token);*/
}
