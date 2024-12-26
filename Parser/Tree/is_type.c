#include "../../Include/minishell.h"

int	is_redir(t_type type)
{
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	need_transfer(t_tokens *right)
{
	if (right->first && right->first->next)
		return (1);
	return (0);
}

t_node	*is_type1(t_node *last)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_node	*is_type2(t_node *last)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_node	*is_type3(t_node *last)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == OUTPUT \
		|| tmp->type == APPEND || tmp->type == HEREDOC)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
