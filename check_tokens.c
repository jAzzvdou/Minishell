#include "minishell.h"

int     check_tokens(t_tokens *tokens)
{
        e_type  type;
        t_node  *first;
        t_node  *last;

        first = tokens->first;
        last = tokens->last;
        type = first->type;
        if (type == PIPE || type == OR || type == AND)
                return (error_syntax(tokens->first->cmd, 1));
        type = last->type;
        if (type == PIPE || type == OR || type == AND
		|| type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
                return (error_syntax(NULL, 2));
        while (first->next)
        {
                type = first->type;
                if (type == PIPE || type == OR || type == AND)
                {
                        type = first->next->type;
                        if (type == PIPE || type == OR || type == AND)
                                return (error_syntax(first->next->cmd, 1));
                }
                first = first->next;
        }
        return (1);
}
