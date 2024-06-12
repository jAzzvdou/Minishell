#include "minishell.h"

int     error_syntax(char *cmd)
{
        printf(GREY"minishell: syntax error near unexpected token `%s'\n",
                cmd);
	return (0);
}

int	is_012(e_type type)
{
	if (type == AND || type == OR || type == PIPE)
		return (0);
	return (1);
}

int     check_tokens(t_tokens *tokens)
{
	e_type  first;
	e_type  last;

	first = tokens->first->type;
	last = tokens->last->type;
	printf("first: %d\n", first);
	printf("last: %d\n", last);
	return (1);
}
