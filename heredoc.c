#include "minishell.h"

int	start_heredoc(t_main *main, t_node *token)
{
	(void)main;
	(void)token;
	return (1);
}

int     is_there_heredoc(t_main *main, t_tokens *tokens)
{
        t_node  *token;

        token = tokens->first;
        while (token)
        {
                if (token->type == HEREDOC)
                {
                        if (!start_heredoc(main, token->next))
                                return (0);
                }
                token = token->next;
        }
        return (1);
}
