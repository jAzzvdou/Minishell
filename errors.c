#include "minishell.h"

// LEMBRAR DE COLOCAR OS ERROS NA SAIDA DE ERRO (2)

int	error_argc(void)
{
	printf(RED"Error!\n");
	printf(GREY"\tUsage:"YELLOW"./minishell\n");
	return (1);
}

int     error_syntax(char *cmd, int option)
{
	if (option == 1)
		printf(GREY"minishell: syntax error near unexpected token `%s'\n",
			cmd);
	else if (option == 2)
		printf(GREY"minishell: syntax error near unexpected token `newline'\n");
        return (0);
}

void	error_env(char *cmd)
{
	printf(GREY"env: '%s': No such file or directory\n", cmd);
}

void    error_exit(char *token, int option)
{
        if (option == 1)
        {
                printf(ORANGE"exit\n"RESET);
                printf(GREY"bash: exit: %s: numeric argument required\n"RESET,
                        token);
        }
        else
        {
                (void)token;
                printf(ORANGE"exit\n"RESET);
                printf(GREY"bash: exit: too many arguments\n"RESET);
        }
}

void	*error_closed(void)
{
	printf(RED"Error!\n");
	printf(GREY"\tMinishell Only Parses Closed Quotes/Parenthesis.\n");
	return (NULL);
}
