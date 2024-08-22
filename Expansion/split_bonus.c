/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:05:23 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/22 15:10:02 by btaveira         ###   ########.fr       */
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

char	*extract_non_dollar(char *cmd, int *i)
{
	char	*start;
	int		len;

	start = &cmd[*i];
	while (cmd[*i] && cmd[*i] != '$')
		(*i)++;
	len = *i - (start - cmd);
	return (ft_strndup(start, len));
}

char	*extract_dollar_sequence(char *cmd, int *i)
{
	char	*start;
	int		len;

	start = &cmd[*i];
	(*i)++;
	while (cmd[*i] && can_continue_bonus(cmd[*i]))
		(*i)++;
	len = *i - (start - cmd);
	return (ft_strndup(start, len));
}

char	**split_bonus(char *cmd)
{
	int		i;
	int		j;
	int		size;
	char	**split;

	size = count_variables_bonus(cmd);
	split = malloc(sizeof(char *) * (size + 1));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] != '$')
		{
			split[i] = extract_non_dollar(cmd, &i);
			j++;
		}
		else if (cmd[i] && cmd[i] == '$')
		{
			split[i] = extract_non_dollar(cmd, &i);
			j++;
		}
	}
	split[j] = NULL;
	free(cmd);
	return (split);
}
