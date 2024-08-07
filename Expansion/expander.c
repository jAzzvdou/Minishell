/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:36:53 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/07 17:04:17 by btaveira         ###   ########.fr       */
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

char	*concatenator(char **matrix)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	len = 0;
	while(matrix[i])
	{
		len+= ft_strlen(matrix[i]);
		i++;
	}
	new_str = malloc(sizeof(char) * len + 1);
	i = 0;
	len = 0;
	while(matrix[i])
	{
		j = 0;
		while(matrix[i][j])
		{
			new_str[len] = matrix[i][j];
			j++;
		}
		i++;
	}
	new_str[len] = '\0';
	free_matrix(matrix);
	return(new_str);
}

/*char	*handle_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[0];

}*/

int	is_valid(int c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	|| (c == '0') || (c == '?') || (c == '-') || (c == '_'))
		return (1);
	return (0);
}

char	*find_var(t_main *main,char *var)
{
	t_env	*env;

	if(!is_valid(var[0]))
	{
		free(var);
		var = NULL;
		return (NULL);
	}
	env = main->env;
	while(env)
	{
		if(ft_strcmp(var,env->name) == 0)
		{
			free(var);
			return(env->value);
		}
	}
	return (NULL);
}

int		find_dollar(char *str)
{
	int	i;

	if(!str || !str[0])
		return (0);
	i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*change_var(t_main *main,char *var)
{
	if(var[0] == '\"')
	{
		var = ft_strtrim(var, (char *)var[0]); //handle_quotes(var);
		if(find_dollar(var + 1))
			return (expand(main,var));
	}
	if(var[0] == '$' && var[1])
		var = ft_strndup(var + 1, ft_strlen(var) - 1);
	var = find_var(main,var);
	return (var);
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
			splited[i] = ft_strtrim(splited[i],(char *)splited[i][0]);//handle_quotes(splited[i]); //| Fazer essa função. Remover as aspas.
		else
			splited[i] = change_var(main, splited[i]);
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
		if(splited[i][0] == '\"' || splited[i][0] == '\'')
			splited[i] = ft_strtrim(splited[i],(char *)splited[i][0]);//handle_quotes(splited[i]);
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
