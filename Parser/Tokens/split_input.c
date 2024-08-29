/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:23:30 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/29 14:20:53 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	is_separator(char *str, int i)
{
	if (!ft_strncmp(str + i, ">>", 2) || !ft_strncmp(str + i, "<<", 2)
		|| !ft_strncmp(str + i, "&&", 2)
		|| !ft_strncmp(str + i, "||", 2)
		|| str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

static int	final_split_part1(char **final, char *input, int i, int counter)
{
	if (!strncmp(input + i, ">>", 2) || !strncmp(input + i, "<<", 2) \
		|| !strncmp(input + i, "&&", 2) || !strncmp(input + i, "||", 2))
	{
		final[counter] = strndup(input + i, 2);
		i += 2;
	}
	else
	{
		final[counter] = strndup(input + i, 1);
		i++;
	}
	return (i);
}

int	final_split_part2(char *input, int i)
{
	while (input[i] && !is_separator(input, i))
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
			verify_quote(input, i))
			i = is_quote(input, i);
		else if (input[i] == '(' && verify_parenthesis(input, i))
			i = skip_parenthesis(input, i);
		else
			i++;
	}
	return (i);
}

static char	**final_split(char **final, char *input, int words, int i)
{
	int	start;
	int	counter;

	start = 0;
	counter = 0;
	while (counter < words)
	{
		while (*input && *input == ' ')
			input++;
		start = i;
		if (is_separator(input, i))
			i = final_split_part1(final, input, i, counter);
		else
		{
			i = final_split_part2(input, i);
			final[counter] = ft_strndup(input, i - start);
		}
		if (!final[counter])
			return (NULL);
		counter++;
		input += i;
		i = 0;
	}
	final[counter] = NULL;
	return (final);
}

char	**split_input(char *input)
{
	int		words;
	char	**final;

	if (!input)
		return (NULL);
	words = count_words(input);
	final = (char **)malloc(sizeof(char *) * (words + 1));
	if (!final)
		return (NULL);
	final = final_split(final, input, words, 0);
	if (!final)
		return (NULL);
	return (final);
}
