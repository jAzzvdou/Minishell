/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:36:53 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 17:12:48 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*expand_bonus(t_main *main, char *cmd)
{
	int	i;
	char	**splited;

	splited = split_bonus(cmd);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '$')
			splited[i] = change_var(main, splited[i]);
		if (!splited[i])
			splited[i] = ft_strdup("\0");
		i++;
	}
	return (concatenator(splited));
}

char	*expand(t_main *main, char *cmd)
{
	int	i;
	char	**splited;

	splited = split_variable(cmd);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\'')
			splited[i] = ft_strndup(splited[i] + 1, ft_strlen(splited[i]) - 2);
		else
			splited[i] = change_var(main, splited[i]);
		if (!splited[i])
			splited[i] = ft_strdup("\0");
		i++;
	}
	return (concatenator(splited));
}

char	*not_expand(char *cmd)
{
	int	i;
	char	**splited;

	splited = split_variable(cmd);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\"' || splited[i][0] == '\'')
			splited[i] = ft_strndup(splited[i] + 1, ft_strlen(splited[i]) - 2);
		if (!splited[i])
			splited[i] = ft_strdup("\0");
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
			add_token(expanded, tmp->type, not_expand(tmp->cmd));
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
	expanded = variables(main, tmp);
	//| Free em tokens.
	//| Free em tmp.
	return (expanded);
}
/*
echo "'$"             | Arrumei.
echo "$"              | Arrumei.
echo "'"$USER"'"      | Arrumei.
echo "\"$USER\""      | Arrumei.
echo "'$USER'"        | Arrumei.
echo $1a              | Arrumei.
echo $US"ER"          | Arrumei.
echo $US'ER'          | Arrumei.
echo "$USER '' $USER" | Arrumei.
*/
