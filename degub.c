#include "minishell.h"

void	debug(void)
{
	static int	i;

	i = 1;
	printf(YELLOW"Debug %d.\n"RESET, i);
	i++;
}
