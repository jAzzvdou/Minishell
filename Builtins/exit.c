/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:20:25 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 17:20:26 by jazevedo         ###   ########.fr       */
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
	}
	free_matrix(token);
	free_everything(main);
	exit(last_status(-1));
}
