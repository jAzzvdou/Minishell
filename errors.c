#include "minishell.h"

int	error_argc(void)
{
	printf(RED"Error!\n");
	printf(GREY"\tUsage:"YELLOW"./minishell\n");
	return (1);
}

int     error_syntax(char *cmd)
{
        printf(GREY"minishell: syntax error near unexpected token `%s'\n",
                cmd);
        return (0);
}
