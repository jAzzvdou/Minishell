#include "../Include/minishell.h"

//| AQUI VAMOS EXPANDIR O WILDCARD E AS VARIÁVEIS DE AMBIENTE.

t_tokens	*expander(t_tokens *tokens)
{
	t_tokens	*expanded;
	t_tokens	*tmp;

	tmp = wildcard(tokens); //| Expandir *.
	expanded = expansion(tmp); //| Expandir VAR.
	free(tmp);
	tmp = NULL;
	return (expanded);
}
