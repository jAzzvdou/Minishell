#include "../../Include/minishell.h"

int	is_quote(char *cmd, int i)
{
	if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	else if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	return (i);
}

int	verify_quote(char *cmd, int i)
{
	char	quote;

	quote = cmd[i];
	i++;
	while (cmd[i])
	{
		if (cmd[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

int	skip_quotes(char **s)
{
	char	quote;

	if (**s == '\'' || **s == '"')
		quote = **s;
	else
		return (0);
	(*s)++;
	while (**s && **s != quote)
		(*s)++;
	if (**s)
		(*s)++;
	return (1);
}

int	closed_quotes(const char *s)
{
	char	quote;

	while (*s)
	{
		if (*s == '\'' || *s == '"')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			if (!*s)
				return (0);
		}
		s++;
	}
	return (1);
}

char	*remove_quote(char *trim, char quote)
{
	size_t	trim_size;
	char	s_quote[1];
	char	*new;

	s_quote[0] = quote;
	while (*trim && my_strchr(s_quote, *trim))
		trim++;
	trim_size = my_strlen(trim) - 1;
	while (trim[trim_size] && my_strchr(s_quote, trim[trim_size]))
		trim_size--;
	new = my_substr(trim, 0, trim_size + 1);
	return (new);
}
