/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:39:56 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/24 14:15:10 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	err(char *s)
{
	write(2, s, ft_strlen(s));
}

int	error_argc(void)
{
	err(RED"Error!\n"RESET);
	err(GREY"\nUsage:"YELLOW"./minishell\n"RESET);
	return (1);
}

int	error_syntax(char *cmd, int option)
{
	if (option == 1)
	{
		err(GREY"minishell: syntax error near unexpected token `");
		err(cmd);
		err("'\n"RESET);
	}
	else if (option == 2)
		err(GREY"minishell: syntax error near unexpected token `newline'\n"RESET);
	return (0);
}

void	error_env(char *cmd)
{
	err(GREY"env: '");
	err(cmd);
	err("': No such file or directory\n"RESET);
}

void	error_exit(char *token, int option)
{
	err(ORANGE"exit\n"RESET);
	if (option == 1)
	{
		err(GREY"bash: exit: ");
		err(token);
		err(": numeric argument required\n"RESET);
	}
	else
	{
		(void)token;
		err(GREY"bash: exit: too many arguments\n"RESET);
	}
}

void	*error_closed(void)
{
	err(RED"Error!\n");
	err(GREY"\tMinishell Only Parses Closed Quotes/Parenthesis.\n"RESET);
	return (NULL);
}
