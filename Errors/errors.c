#include "../Include/minishell.h"

void	err(char *s)
{
	write(STDERR_FILENO, s, my_strlen(s));
}

int	error_argc(void)
{
	err(RED"Error!\n"RESET);
	err(GREY"\tUsage:"YELLOW"./minishell\n"RESET);
	return (1);
}

int	error_syntax(char *cmd, int option)
{
	if (option == 1)
	{
		err(GREY"minichad: syntax error near unexpected token `");
		err(cmd);
		err("'\n"RESET);
	}
	else if (option == 2)
	{
		err(GREY"minichad: syntax error near");
		err(" unexpected token `newline'\n"RESET);
	}
	last_status(2);
	return (0);
}

void	error_env(char *cmd)
{
	err(GREY"env: '");
	err(cmd);
	err("': No such file or directory\n"RESET);
}

void	*error_closed(void)
{
	err(RED"Error!\n");
	err(GREY"\tMinichad Only Parses Closed Quotes/Parenthesis.\n"RESET);
	return (NULL);
}
