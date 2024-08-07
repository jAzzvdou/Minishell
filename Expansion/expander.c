/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:36:53 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/07 15:12:34 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] != ' ')
			is_var = 1;
		i++;
	}
	return (is_var);
}

char	*expand(t_main *main, char *cmd)
{
	int	i;
	char	**splited;

	splited = split_variable(cmd); //| Fazer essa função. Splitar cmd em novas strings.
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\'')
			splited[i] = handle_quotes(splited[i]); //| Fazer essa função. Remover as aspas.
		else
			splited[i] = search_var(splited[i]); //| Fazer essa função. Pesquisar o VAR em ENV e substituir.
		i++;
	}
	return (concatenator(splited)); //| Fazer essa função. Concatenar todas as strings de splited em uma só.
}

char	*not_expand(char *cmd)
{
	int	i;
	char	**splited;

	splited = split_variable(cmd);
	i = 0;
	while (splited[i])
	{
		splited[i] = handle_quotes(splited[i]);
		i++;
	}
	return (concatenator(splited));
}

t_tokens	*variables(t_main *main, t_tokens *tokens)
{
	t_node		*tmp;
	t_tokens	*expanded;

	expanded = start_tokens();
	tmp = tokens->first;
	while (tmp)
	{
		if (is_var(tmp->cmd))
			add_token(expanded, tmp->type, expand(main, tmp->cmd));
		else
			add_token(expaded, tmp->type, not_expand(tmp->cmd));
		tmp = tmp->next;
	}
	// Free em tokens.
	return (expanded);
}

t_tokens	*expander(t_main *main, t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*expanded;

	tmp = wildcard(tokens);
	expand = variables(main, tmp);
	//| Free em tokens.
	//| Free em tmp.
	return (expanded);
}
