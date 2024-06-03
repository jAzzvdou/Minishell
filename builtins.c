#include "minishell.h"

///////////////////////////////////////////////////////////////////////////////
//| PARA TESTES, DEPOIS TEM QUE ORGANIZAR.
int	is_number(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}

int	only_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	while (s[i])
		if (!is_number(s[i++]))
			return (0);
	return (1);
}

long long	ft_atoll(const char *nptr)
{
	long long	nb;
	int		mult;

	nb = 0;
	mult = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		mult = -mult;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (nb * mult);
}

int	is_long(char *argv)
{
	if (ft_strlen(argv) > 20
		|| ft_atoll(argv) > LONG_MAX
		|| ft_atoll(argv) < LONG_MIN)
		return (0);
	return (1);
}
///////////////////////////////////////////////////////////////////////////////
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
		printf(ORANGE"exit\n"RESET);
		printf(GREY"bash: exit: %s: numeric argument required\n"RESET,
			token[1]);
		exit(1);
	}
	if (token[1] && token[2])
	{
		static_env(NULL, FREE);
		printf(ORANGE"exit\n"RESET);
		printf(GREY"bash: exit: too many arguments\n"RESET);
		exit(1);
	}
	static_env(NULL, FREE);
	printf(ORANGE"exit\n"RESET);
	exit(1);
}

void	pwd_cmd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}

void	controller(char **token)
{
	if (!strcmp(token[0], "exit"))
		exit_cmd(token);
	else if (!strcmp(token[0], "env"))
		env_cmd(token);
	//else if (!strcmp(token[0], "echo"))
	//	echo_cmd(token);
	else if (!strcmp(token[0], "pwd"))
		pwd_cmd();
	/*else if (!strcmp(token[0], "cd"))
		cd_cmd(token);
	else if (!strcmp(token[0], "export"))
		export_cmd(token);
	else if (!strcmp(token[0], "unset"))
		unset_cmd(token);*/
}
