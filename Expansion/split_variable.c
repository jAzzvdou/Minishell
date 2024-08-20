/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:08:57 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/20 16:25:00 by btaveira         ###   ########.fr       */
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
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (cmd[i])
	{
		i = skip_spaces_split_variable(cmd, i);
		if (cmd[i] == '\0')
			break ;
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i = handle_quote_segment(cmd, i, &words);
		else if (cmd[i] == '$')
			i = handle_dollar_segment(cmd, i, &words);
		else
			i = handle_regular_segment(cmd, i, &words);
		i = skip_spaces_split_variable(cmd, i);
	}
	return (words);
}

char	**split_variable(char *cmd)
{
	int		i;
	int		j;
	int		size;
	char	**split;

	i = 0;
	j = 0;
	size = count_variables(cmd);
	split = malloc(sizeof(char *) * (size + 1));
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			split_variables_1(&cmd, &i, split, &j);
		else if (cmd[i] == '\'' || cmd[i] == '\"')
			split_variables_2(&cmd, &i, split, &j);
		else if (cmd[i] == '$')
			split_variables_3(&cmd, &i, split, &j);
		else
			split_variables_4(&cmd, &i, split, &j);
	}
	split[j] = NULL;
	return (split);
}
