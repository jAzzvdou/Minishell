#include "../Include/minishell.h"

int	is_var(char *cmd)
{
	int	i;
	int	is_var;

	if (!cmd || !cmd[0])
		return (0);
	is_var = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && cmd[i + 1]
			&& cmd[i + 1] != ' ' && cmd[i + 1] != '\'')
			is_var = 1;
		i++;
	}
	return (is_var);
}

int	is_valid(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c == '0') || (c == '?') || (c == '-') || (c == '_'))
		return (1);
	return (0);
}
