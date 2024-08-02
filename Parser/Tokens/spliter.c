/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:23 by bruno             #+#    #+#             */
/*   Updated: 2024/08/02 12:33:26 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static	void	free_split(char **final)
{
	int		i;

	i = -1;
	while (final[++i])
		free(final[i]);
	free(final);
}

static	int	count_words(char *cmd)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			words++;
		if ((cmd[i] == '\'' || cmd[i] == '\"') && verify_quote(cmd, i))
			i += is_quote(cmd, i);
		else if ((cmd[i] == '(' && verify_parenthesis(cmd, i)))
			i += skip_parenthesis(cmd, i);
		while (cmd[i] && cmd[i] != ' ')
			cmd++;
		while (cmd[i] && cmd[i] == ' ')
			cmd++;
	}
	return (words);
}

static	char	**final_split(char **final, char *cmd, int words)
{
	int	i;
	int	counter;

	counter = -1;
	while (++counter < words)
	{
		while (*cmd == ' ')
			cmd++;
		i = 0;
		if ((cmd[i] == '\'' || cmd[i] == '\"') && verify_quote(cmd, i))
			i += is_quote(cmd, i);
		else if ((cmd[i] == '(' && verify_parenthesis(cmd, i)))
			i += skip_parenthesis(cmd, i);
		while (cmd[i] && cmd[i] != ' ')
			i++;
		final[counter] = ft_substr(cmd, 0, i);
		if (!final[counter])
			return (free_split(final), NULL);
		cmd += i;
	}
	return (final[counter] = NULL, final);
}

char	**spliter(char *cmd)
{
	int		words;
	char	**final;
	char	**trim;

	if (!cmd)
		return (NULL);
	words = count_words(cmd);
	final = (char **)malloc(sizeof(char *) * (words + 1));
	if (!final)
		return (NULL);
	trim = final_split(final, cmd, words);
	return (trim);
}
