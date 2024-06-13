#include "minishell.h"

void	exit_cmd(char **token)
{
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
		error_exit(token[1], 1);
	else if (token[1] && token[2])
		error_exit(token[1], 2);
	else
		printf(ORANGE"exit\n"RESET);
	//| FREE ALL
	exit(1);
}
