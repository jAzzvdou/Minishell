#include "../../Include/minishell.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	skip_spaces(char **s)
{
	while (**s && is_space(**s))
		(*s)++;
}
