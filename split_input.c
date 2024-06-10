#include "minishell.h"

static int	verify_quote2(const char *str, int index)
{
	char	quote;

	index++;
	quote = str[index];
	while (str[index])
	{
		if (str[index] == quote)
			return (index);
		index++;
	}
	return (-1);
}

static int	skip_parenthesis2(const char *str, int index)
{
	int	count;

	index++;
	count = 1;
	while (str[index] && count > 0)
	{
		if (str[index] == '(')
			count++;
		else if (str[index] == ')')
			count--;
		index++;
	}
	return (index - 1);
}

static int	is_separator(const char *str, int i)
{
	if (!ft_strncmp(str + i, ">>", 2) || !ft_strncmp(str + i, "<<", 2)
		|| !ft_strncmp(str + i, "&&", 2)
		|| !ft_strncmp(str + i, "||", 2)
		|| str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

static int	count_words(const char *input)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' '))
			i++;
		if (input[i])
			words++;
		while (input[i] && !is_separator(input, i))
		{
			if ((input[i] == '\'' || input[i] == '\"')
				&& verify_quote2(input, i) > 0)
				i = verify_quote2(input, i) + 1;
			else if (input[i] == '(' && skip_parenthesis2(input, i) > 0)
				i = skip_parenthesis2(input, i) + 1;
			else
				i++;
		}
		if (input[i] && is_separator(input, i))
		{
			words++;
			if (!ft_strncmp(input + i, ">>", 2)
				|| !ft_strncmp(input + i, "<<", 2)
				|| !ft_strncmp(input + i, "&&", 2)
				|| !ft_strncmp(input + i, "||", 2))
				i += 2;
			else
				i++;
		}
	}
	return (words);
}

static char	**final_split(char **final, const char *input, int words)
{
	int	i;
	int	counter;
	int	start;

	i = 0;
	counter = 0;
	while (counter < words)
	{
		while (*input && (*input == ' '))
			input++;
		start = i;
		while (input[i] && !is_separator(input, i))
		{
			if ((input[i] == '\'' || input[i] == '\"')
				&& verify_quote2(input, i) > 0)
				i = verify_quote2(input, i) + 1;
			else if (input[i] == '(' && skip_parenthesis2(input, i) > 0)
				i = skip_parenthesis2(input, i) + 1;
			else
				i++;
		}
		final[counter] = ft_strndup(input, i - start);
		if (!final[counter])
			return (NULL);
		counter++;
		if (input[i] && is_separator(input, i))
		{
			if (!ft_strncmp(input + i, ">>", 2)
				|| !ft_strncmp(input + i, "<<", 2)
				|| !ft_strncmp(input + i, "&&", 2)
				|| !ft_strncmp(input + i, "||", 2))
			{
				final[counter] = ft_strndup(input + i, 2);
				i += 2;
			}
			else
			{
				final[counter] = ft_strndup(input + i, 1);
				i++;
			}
			counter++;
		}
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
	final = final_split(final, input, words);
	if (!final)
		return (NULL);
	return (final);
}
