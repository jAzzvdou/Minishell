/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:08 by bruno             #+#    #+#             */
/*   Updated: 2024/07/03 16:05:59 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exit_cmd(t_main *main, char **token)
{
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
	{
		error_exit(token[1], 1); // erro = 2
		last_status(2);
	}
	else if (token[1] && token[2])
	{
		error_exit(token[1], 2); // erro = 1
		last_status(1);
		free_matrix(token);
		return ;
	}
	else
	{
		err(ORANGE"exit\n"RESET);
		if (token[1] && token[1][0])
			last_status(ft_atoll(token[1]));
		else
			last_status(0);
	}
	free_matrix(token);
	free_everything(main);
	exit(0); //| EXIT_SUCCESS
}
