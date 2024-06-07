#include "minishell.h"

static void	free_split(char **final)
{
	size_t	i;

	i = -1;
	while (final[++i])
		free(final[i]);
	free(final);
}

static size_t	sub_str(char const *s, char c)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		if (*s != c)
			length++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (length);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	words;
	size_t	wordsize;
	char	**final;

	if (!s)
		return (NULL);
	words = sub_str(s, c);
	final = malloc(sizeof(char *) * (words + 1));
	if (!final)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		wordsize = 0;
		while (s[wordsize] && s[wordsize] != c)
			wordsize++;
		final[i] = ft_substr(s, 0, wordsize);
		if (final[i] == NULL)
			return (free_split(final), NULL);
		s += wordsize;
	}
	return (final[i] = NULL, final);
}
