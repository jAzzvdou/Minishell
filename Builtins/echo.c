#include "../Include/minishell.h"

int	check_flag(char *token)
{
	if (token && !my_strcmp(token, "-n"))
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
	last_status(0);
}
