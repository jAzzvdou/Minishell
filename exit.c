#include "minishell.h"

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
