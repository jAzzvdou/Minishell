/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:08:57 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/28 19:00:03 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	can_continue(int c)
{
	if (c == ' ' || c == '\'' || c == '\"' || c == '$')
		return (0);
	return (1);
}

void skip_quotes_var(char *cmd, int *i, int *words)
{
	char quote;

	(*words)++;
	quote = cmd[(*i)++];
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (cmd[*i] == quote)
		(*i)++;
}

void skip_dollar_var(char *cmd, int *i, int *words)
{
	(*words)++;
	(*i)++;
	while (cmd[*i] && can_continue(cmd[*i]))
		(*i)++;
}

void skip_word_var(char *cmd, int *i, int *words)
{
	(*words)++;
	while (cmd[*i] && can_continue(cmd[*i]))
		(*i)++;
}
int	count_variables(char *cmd)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i] == '\0')
			break ;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
			skip_quotes_var(cmd, &i, &words);
		else if (cmd[i] == '$')
			skip_dollar_var(cmd, &i, &words);
		else
			skip_word_var(cmd, &i, &words);
		while (cmd[i] && cmd[i] == ' ')
		{
			words++;
			i++;
		}
	}
	return (words);
}

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


char	**split_variable(char *cmd)
{
	int		i[3];
	char	**split;

	i[2] = count_variables(cmd);
	split = malloc(sizeof(char *) * (i[2] + 1));
	i[0] = 0;
	i[1] = 0;
	while (cmd[i[0]])
	{
		split_spaces(split, cmd, &i[0], &i[1]);
		if (cmd[i[0]] == '\0')
			break ;
		else if (cmd[i[0]] == '\'' || cmd[i[0]] == '\"')
			split[i[1]++] = split_quote(cmd, &i[0]);
		else if (cmd[i[0]] == '$')
			split[i[1]++] = split_dollar(cmd, &i[0]);
		else
			split[i[1]++] = split_word(cmd, &i[0]);
		split_spaces(split, cmd, &i[0], &i[1]);
	}
	return (split[i[1]] = NULL, split);
}
