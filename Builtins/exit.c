#include "../Include/minishell.h"

long long	exit_status_calculator(char *token)
{
	long long	nb;

	nb = my_atoll(token);
	while (nb < 0)
		nb = 256 + nb;
	return (nb);
}

void	exit_cmd(t_main *main, char **token)
{
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
	{
		error_exit(token[1], 1);
		last_status(2);
	}
	else if (token[1] && token[2])
	{
		error_exit(token[1], 2);
		last_status(1);
		return ;
	}
	else
	{
		err(ORANGE"exit\n"RESET);
		if (token[1] && token[1][0])
			last_status(exit_status_calculator(token[1]));
	}
	free_matrix(token);
	free_everything(main);
	exit(last_status(-1));
}
