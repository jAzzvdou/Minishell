/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:05:23 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/28 14:18:05 by btaveira         ###   ########.fr       */
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

char	**split_bonus_loop(char **split, char *cmd, int *i)
{
	char	*start;

	while (cmd[i[0]])
	{
		if (cmd[i[0]] && cmd[i[0]] != '$')
		{
			start = &cmd[i[0]];
			while (cmd[i[0]] && cmd[i[0]] != '$')
				i[0]++;
			split[i[1]] = ft_strndup(start, i[0] - (start - cmd));
			i[1]++;
		}
		else if (cmd[i[0]] && cmd[i[0]] == '$')
		{
			start = &cmd[i[0]];
			i[0]++;
			while (cmd[i[0]] && can_continue_bonus(cmd[i[0]]))
				i[0]++;
			split[i[1]] = ft_strndup(start, i[0] - (start - cmd));
			i[1]++;
		}
	}
	return (split[i[1]] = NULL, split);
}

char	**split_bonus(char *cmd)
{
	int		size;
	char	**split;
	int		i[2];

	size = count_variables_bonus(cmd);
	split = malloc(sizeof(char *) * (size + 1));
	i[0] = 0;
	i[1] = 0;
	split = split_bonus_loop(split, cmd, i);
	free(cmd);
	return (split);
}
