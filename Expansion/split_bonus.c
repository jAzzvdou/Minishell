/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:05:23 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/12 19:06:19 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	can_continue_bonus(int c)
{
	if (c == ' ' || c == '\'' || c == '\\')
		return (0);
	return (1);
}

int	count_variables_bonus(char *cmd)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '$')
		{
			words++;
			while (cmd[i] && cmd[i] != '$')
				i++;
		}
		else if (cmd[i] == '$')
		{
			words++;
			while (cmd[i] && can_continue_bonus(cmd[i]))
				i++;
		}
	}
	return (words);
}

char	**split_bonus(char *cmd)
{
	int	i;
	int	j;
	int	size;
	char	*start;
	char	**split;

	size = count_variables_bonus(cmd);
	split = malloc(sizeof(char *) * size + 1);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] != '$')
		{
			start = &cmd[i];
			while (cmd[i] && cmd[i] != '$')
				i++;
			split[j] = ft_strndup(start, i - (start - cmd));
			j++;
		}
		else if (cmd[i] == '$')
		{
			start = &cmd[i];
			i++;
			while (cmd[i] && can_continue_bonus(cmd[i]))
				i++;
			split[j] = ft_strndup(start, i - (start - cmd));
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}
