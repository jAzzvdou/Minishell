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
                return (error_syntax(tokens->first->cmd));
        type = last->type;
        if (type == PIPE || type == OR || type == AND)
                return (error_syntax(tokens->last->cmd));
        while (first->next)
        {
                type = first->type;
                if (type == PIPE || type == OR || type == AND)
                {
                        type = first->next->type;
                        if (type == PIPE || type == OR || type == AND)
                                return (error_syntax(first->next->cmd));
                }
                first = first->next;
        }
        return (1);
}
