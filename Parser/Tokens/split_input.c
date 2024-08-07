/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:28 by bruno             #+#    #+#             */
/*   Updated: 2024/07/08 13:24:10 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	is_separator(char *str, int i)
{
	if (!ft_strncmp(str + i, ">>", 2) || !ft_strncmp(str + i, "<<", 2)
		|| !ft_strncmp(str + i, "&&", 2)
		|| !ft_strncmp(str + i, "||", 2)
		|| str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

static int	count_words(char *input)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		words++;
		if (is_separator(input, i))
		{
			if (!strncmp(input + i, ">>", 2) || !strncmp(input + i, "<<", 2) \
			|| !strncmp(input + i, "&&", 2) || !strncmp(input + i, "||", 2))
				i += 2;
			else
				i++;
		}
		else
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
		}
	}
	return (words);
}

static char	**final_split(char **final, char *input, int words)
{
	int	i;
	int	start;
	int	counter;

	i = 0;
	start = 0;
	counter = 0;
	while (counter < words)
	{
		while (*input && *input == ' ')
			input++;
		start = i;
		if (is_separator(input, i))
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
		}
		else
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
			final[counter] = strndup(input, i - start);
		}
		if (!final[counter])
			return (NULL);
		counter++;
		input += i;
		i = 0;
	}
	final[counter] = (NULL);
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
	final = final_split(final, input, words);
	if (!final)
		return (NULL);
	return (final);
}
