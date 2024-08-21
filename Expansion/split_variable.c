/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:08:57 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/21 16:28:08 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	can_continue(int c)
{
	if (c == ' ' || c == '\'' || c == '\"' || c == '$')
		return (0);
	return (1);
}

int	count_variables(char *cmd)
{
	int		i;
	int		words;
	char	quote;

	words = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i] == '\0')
			break ;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			words++;
			quote = cmd[i++];
			while (cmd[i] && cmd[i] != quote)
				i++;
			if (cmd[i] == quote)
				i++;
		}
		else if (cmd[i] == '$')
		{
			words++;
			i++;
			while (cmd[i] && can_continue(cmd[i]))
				i++;
		}
		else
		{
			words++;
			while (cmd[i] && can_continue(cmd[i]))
				i++;
		}
		while (cmd[i] && cmd[i] == ' ')
		{
			words++;
			i++;
		}
	}
	return (words);
}

char	**split_variable(char *cmd)
{
	int		i[3];
	char	quote;
	char	*start;
	char	**split;

	i[2] = count_variables(cmd);
	split = malloc(sizeof(char *) * (i[2] + 1));
	i[0] = 0;
	i[1] = 0;
	while (cmd[i[0]])
	{
		while (cmd[i[0]] && cmd[i[0]] == ' ')
		{
			start = &cmd[i[0]];
			while (cmd[i[0]] && cmd[i[0]] == ' ')
				i[0]++;
			split[i[1]++] = ft_strndup(start, i[0] - (start - cmd));
		}
		if (cmd[i[0]] == '\0')
			break ;
		else if (cmd[i[0]] == '\'' || cmd[i[0]] == '\"')
		{
			start = &cmd[i[0]];
			quote = cmd[i[0]++];
			while (cmd[i[0]] && cmd[i[0]] != quote)
				i[0]++;
			if (cmd[i[0]] == quote)
				i[0]++;
			split[i[1]++] = ft_strndup(start, i[0] - (start - cmd));
		}
		else if (cmd[i[0]] == '$')
		{
			start = &cmd[i[0]];
			i[0]++;
			while (cmd[i[0]] && can_continue(cmd[i[0]]))
				i[0]++;
			split[i[1]++] = ft_strndup(start, i[0] - (start - cmd));
		}
		else
		{
			start = &cmd[i[0]];
			while (cmd[i[0]] && can_continue(cmd[i[0]]))
				i[0]++;
			split[i[1]++] = ft_strndup(start, i[0] - (start - cmd));
		}
		while (cmd[i[0]] && cmd[i[0]] == ' ')
		{
			start = &cmd[i[0]];
			while (cmd[i[0]] && cmd[i[0]] == ' ')
				i[0]++;
			split[i[1]++] = ft_strndup(start, i[0] - (start - cmd));
		}
	}
	split[i[1]] = NULL;
	return (split);
}
