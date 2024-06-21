/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:08 by bruno             #+#    #+#             */
/*   Updated: 2024/06/21 00:21:03 by jazevedo         ###   ########.fr       */
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
		printf(ORANGE"exit\n"RESET);
	free_matrix(token);
	free_everything(main);
	exit(1);
}
