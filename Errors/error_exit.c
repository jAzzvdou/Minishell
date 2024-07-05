/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:44:20 by btaveira          #+#    #+#             */
/*   Updated: 2024/07/02 14:45:03 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	error_exit(char *token, int option)
{
	err(ORANGE"exit\n"RESET);
	if (option == 1)
	{
		err(GREY"minichad: exit: ");
		err(token);
		err(": numeric argument required\n"RESET);
	}
	else
	{
		(void)token;
		err(GREY"minichad: exit: too many arguments\n"RESET);
	}
}
