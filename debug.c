#include "Include/minishell.h"

void	debug(void)
{
	int	start;
	static int	i;

	start = 0;
	i = start + i + 1;
	printf(YELLOW"Debug %d.\n"RESET, i);
}
