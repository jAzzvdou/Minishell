/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:23:46 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/29 14:25:07 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	split_spaces(char **split, char *cmd, int *i, int *j)
{
	char	*start;

	while (cmd[*i] && cmd[*i] == ' ')
	{
		start = &cmd[*i];
		while (cmd[*i] && cmd[*i] == ' ')
			(*i)++;
		split[(*j)++] = ft_strndup(start, *i - (start - cmd));
	}
}

char	*skip_spaces_split(char *cmd, int *i)
{
	char	*start;

	start = &cmd[*i];
	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
	return (ft_strndup(start, *i - (start - cmd)));
}

char	*split_quote(char *cmd, int *i)
{
	char	quote;
	char	*start;

	start = &cmd[*i];
	quote = cmd[(*i)++];
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (cmd[*i] == quote)
		(*i)++;
	return (ft_strndup(start, *i - (start - cmd)));
}

char	*split_dollar(char *cmd, int *i)
{
	char	*start;

	start = &cmd[*i];
	(*i)++;
	while (cmd[*i] && can_continue(cmd[*i]))
		(*i)++;
	return (ft_strndup(start, *i - (start - cmd)));
}

char	*split_word(char *cmd, int *i)
{
	char	*start;

	start = &cmd[*i];
	while (cmd[*i] && can_continue(cmd[*i]))
		(*i)++;
	return (ft_strndup(start, *i - (start - cmd)));
}
