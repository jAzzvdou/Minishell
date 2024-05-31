#include "minishell.h"

int	error_argc(void)
{
	printf(RED"Error!\n");
	printf(GREY"\tUsage:"YELLOW"./minishell\n");
	return (1);
}
