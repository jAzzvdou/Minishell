#include "minishell.h"

void	env_cmd(t_main *main, char **token)
{
	int	i;
	t_env	*env;

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
	env = main->env;
	while (env)
	{
		printf(WHITE"%s\n"RESET, env->line);
		env = env->next;
	}
}

void	exit_cmd(char **token)
{
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
	{
		printf(ORANGE"exit\n"RESET);
		printf(GREY"bash: exit: %s: numeric argument required\n"RESET,
			token[1]);
		exit(1);
	}
	if (token[1] && token[2])
	{
		printf(ORANGE"exit\n"RESET);
		printf(GREY"bash: exit: too many arguments\n"RESET);
		exit(1);
	}
	printf(ORANGE"exit\n"RESET);
	exit(1);
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

void	controller(t_main *main, char **token)
{
	if (!strcmp(token[0], "exit"))
		exit_cmd(token);
	else if (!strcmp(token[0], "env"))
		env_cmd(main, token);
	else if (!strcmp(token[0], "pwd"))
		printf("%s\n", main->pwd);
	else if (!strcmp(token[0], "echo"))
		echo_cmd(token); //| LEMBRAR DE TRATAR '$0' E '$$'.
	/*else if (!strcmp(token[0], "export"))
		export_cmd(token);
	else if (!strcmp(token[0], "unset"))
		unset_cmd(token);
	else if (!strcmp(token[0], "cd"))
		cd_cmd(token);*/
}
