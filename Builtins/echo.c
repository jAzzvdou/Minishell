/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:35 by bruno             #+#    #+#             */
/*   Updated: 2024/08/08 16:08:46 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	check_flag(char *token)
{
	if (token && !ft_strcmp(token, "-n"))
		return (1);
	return (0);
}

void	echo_cmd(char **token)
{
	int	i;
	int	space;
	int	newline;

	i = 1;
	newline = 1;
	while (check_flag(token[i]))
	{
		i++;
		newline = 0;
	}
	space = 0;
	while (token[i])
	{
		if (space)
			printf(" ");
		else
			space++;
		printf("%s", token[i++]);
	}
	if (newline)
		printf("\n");
	last_status(0);
}
