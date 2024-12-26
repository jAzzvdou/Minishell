#include "../../Include/minishell.h"

int	check_start_token(t_type type, t_node *first)
{
	if (type == PIPE || type == OR || type == AND)
		return (error_syntax(first->cmd, 1));
	return (0);
}

int	check_end_token(t_type type)
{
	if (type == PIPE || type == OR || type == AND
		|| type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
		return (error_syntax(NULL, 2));
	return (0);
}

int	check_invalid_sequence(t_node *node)
{
	t_type	type;
	t_type	next_type;

	type = node->type;
	next_type = node->next->type;
	if ((type == PIPE || type == OR || type == AND)
		&& (next_type == PIPE || next_type == OR || next_type == AND))
		return (error_syntax(node->next->cmd, 1));
	else if ((type == INPUT || type == OUTPUT || type == HEREDOC
			|| type == APPEND)
		&& (next_type == PIPE || next_type == OR || next_type == AND
			|| next_type == INPUT || next_type == OUTPUT
			|| next_type == HEREDOC || next_type == APPEND))
		return (error_syntax(node->next->cmd, 1));
	return (0);
}

int	check_tokens(t_tokens *tokens)
{
	t_node	*first;
	t_node	*last;

	first = tokens->first;
	last = tokens->last;
	if (check_start_token(first->type, first))
		return (0);
	if (check_end_token(last->type))
		return (0);
	while (first->next)
	{
		if (check_invalid_sequence(first))
			return (0);
		first = first->next;
	}
	return (1);
}
