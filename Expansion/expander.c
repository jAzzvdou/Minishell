#include "../Include/minishell.h"

//| AQUI VAMOS EXPANDIR O WILDCARD E AS VARIÁVEIS DE AMBIENTE.

t_tokens	*wildcard(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->first->type == CMD
			&& ft_strchr(tmp->first->cmd, '*'))
		{
			//| Pegar a lista depois de *.
			//| tokens -> tokens expandidos.
		}
		tmp = tmp->next;
	}
	return (expanded);
}

t_tokens	*expander(t_tokens *tokens)
{
	t_tokens	*expanded;
	t_tokens	*tmp;

	tmp = wildcard(tokens); //| Expandir *.
	expanded = expansion_var(tmp); //| Expandir VAR.
	free(tmp);
	tmp = NULL;
	return (expanded);
}
