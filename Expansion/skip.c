#include "../Include/minishell.h"

void	skip_quotes_var(char *cmd, int *i, int *words)
{
	char	quote;

	(*words)++;
	quote = cmd[(*i)++];
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (cmd[*i] == quote)
		(*i)++;
}

void	skip_dollar_var(char *cmd, int *i, int *words)
{
	(*words)++;
	(*i)++;
	while (cmd[*i] && can_continue(cmd[*i]))
		(*i)++;
}

void	skip_word_var(char *cmd, int *i, int *words)
{
	(*words)++;
	while (cmd[*i] && can_continue(cmd[*i]))
		(*i)++;
}
