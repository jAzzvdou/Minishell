/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:08 by bruno             #+#    #+#             */
/*   Updated: 2024/06/24 14:21:36 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exit_cmd(t_main *main, char **token)
{
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
		error_exit(token[1], 1);
	else if (token[1] && token[2])
		error_exit(token[1], 2);
	else
		err(ORANGE"exit\n"RESET);
	free_matrix(token);
	free_everything(main);
	exit(1);
}
