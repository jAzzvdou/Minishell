#include "minishell.h"

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
	while (cmd[++i])
		if (cmd[i] == quote)
			return (1);
	return (0);
}

char	*remove_quote(char *trim, char quote)
{
	size_t	trim_size;
	char	s_quote[1];
	char	*new;

	s_quote[0] = quote;
	while (*trim && ft_strchr(s_quote, *trim))
		trim++;
	trim_size = ft_strlen(trim) - 1;
	while (trim[trim_size] && ft_strchr(s_quote, trim[trim_size]))
		trim_size--;
	new = ft_substr(trim, 0, trim_size + 1);
	return (new);
}

static int	count_words(char *cmd)
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
		while (cmd[i] && cmd[i] != ' ')
			cmd++;
		while (cmd[i] && cmd[i] == ' ')
			cmd++;
	}
	return (words);
}

static void	free_split(char **final)
{
	int	i;

	i = -1;
	while (final[++i])
		free(final[i]);
	free(final);
}

static char	**final_split(char **final, char *cmd, int words)
{
	int	counter;
	int	i;

	counter = -1;
	while (++counter < words)
	{
		while (*cmd == ' ')
			cmd++;
		i = 0;
		if ((cmd[i] == '\'' || cmd[i] == '\"') && verify_quote(cmd, i))
			i += is_quote(cmd, i);
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
	int		i;
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
	i = -1;
	while (trim[++i])
	{
		if ((trim[i][0] == '\'' || trim[i][0] == '\"')
			&& verify_quote(trim[i], 0))
			trim[i] = remove_quote(trim[i], trim[i][0]);
	}
	return (trim);
}
