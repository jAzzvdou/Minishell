/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:08:57 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/15 12:09:28 by btaveira         ###   ########.fr       */
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
	int		size;
	char	**split;
	int		i;
	int		j;
	char	*start;
	char	quote;

	i = 0;
	j = 0;
	size = count_variables(cmd);
	split = malloc(sizeof(char *) * (size + 1));
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
		{
			start = &cmd[i];
			while (cmd[i] && cmd[i] == ' ')
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		if (cmd[i] == '\0')
			break ;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			start = &cmd[i];
			quote = cmd[i++];
			while (cmd[i] && cmd[i] != quote)
				i++;
			if (cmd[i] == quote)
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		else if (cmd[i] == '$')
		{
			start = &cmd[i];
			i++;
			while (cmd[i] && can_continue(cmd[i]))
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		else
		{
			start = &cmd[i];
			while (cmd[i] && can_continue(cmd[i]))
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		while (cmd[i] && cmd[i] == ' ')
		{
			start = &cmd[i];
			while (cmd[i] && cmd[i] == ' ')
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
	}
	split[j] = NULL;
	return (split);
}
