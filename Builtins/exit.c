/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:08 by bruno             #+#    #+#             */
/*   Updated: 2024/07/10 11:57:26 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exit_cmd(t_main *main, char **token)
{
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
	{
		error_exit(token[1], 1);
		last_status(2);
	}
	else if (token[1] && token[2])
	{
		error_exit(token[1], 2);
		last_status(1);
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
	printf("last status: %d\n", last_status(-1));
	if (last_status(-1))
		exit(last_status(-1));
	exit(1);
}
