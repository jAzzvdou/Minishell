#include "../Include/minishell.h"

int	can_continue(int c)
{
	if (c == ' ' || c == '\'' || c == '\"' || c == '$')
		return (0);
	return (1);
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
