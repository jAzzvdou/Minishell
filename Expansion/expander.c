/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:36:53 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 14:39:04 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*expand(t_main *main, char *cmd);

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
		if (cmd[i] == '$' && cmd[i + 1]
			&& cmd[i + 1] != ' ' && cmd[i + 1] != '\'')
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
	while (matrix[i])
	{
		len += ft_strlen(matrix[i]);
		i++;
	}
	new_str = malloc(sizeof(char) * len + 1);
	i = 0;
	len = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			new_str[len] = matrix[i][j];
			j++;
			len++;
		}
		i++;
	}
	new_str[len] = '\0';
	free_matrix(matrix);
	return (new_str);
}

int	is_valid(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c == '0') || (c == '?') || (c == '-') || (c == '_'))
		return (1);
	return (0);
}

char	*find_var(t_main *main, char *var)
{
	char	*tmp;
	t_env	*env;

	tmp = NULL;
	if (!is_valid(var[0]))
	{
		if (is_number(var[0]) && var[0] != '0')
			tmp = ft_strndup(var + 1, ft_strlen(var) - 1);
	}
	if (var[0] == '0')
		tmp = ft_strdup("minichad");
	else if (var[0] == '?')
		tmp = ft_itoa(last_status(-1));
	else if (var[0] == '-')
		tmp = ft_strdup("himBHs");
	env = main->env;
	while (env && !tmp)
	{
		if (!ft_strcmp(var, env->name))
			tmp = ft_strdup(env->value);
		env = env->next;
	}
	free(var);
	var = NULL;
	return (tmp);
}

int	find_dollar(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*change_var(t_main *main, char *var)
{
	printf("Before var = |%s|\n", var);
	if (var[0] == '\"')
	{
		var = ft_strndup(var + 1, ft_strlen(var) - 2);
		printf("After var = |%s|\n", var);
		//| Tratar "'$USER'"
		if (find_dollar(var))
			return (expand(main, var));
	}
	if (var[0] == '$' && var[1])
	{
		var = ft_strndup(var + 1, ft_strlen(var) - 1);
		var = find_var(main, var);
	}
	return (var);
}

int	can_continue(int c)
{
	if (c == ' ' || c == '\'' || c == '\"' || c == '$')
		return (0);
	return (1);
}

int	count_variables(char *cmd)
{
	int	i;
	int	words;
	char	quote;

	words = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i] == '\0')
			break;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			words++;
			quote = cmd[i++];
			while (cmd[i] && cmd[i] != quote)
				i++;
			if (cmd[i] == quote)
				i++;
		}
		else if (cmd[i] == '$')
		{
			words++;
			i++;
			while (cmd[i] && can_continue(cmd[i]))
				i++;
		}
		else
		{
			words++;
			while (cmd[i] && can_continue(cmd[i]))
				i++;
		}
		while (cmd[i] && cmd[i] == ' ')
			words++, i++;
	}
	return (words);
}

char	**split_variable(char *cmd)
{
	int size = count_variables(cmd);
	char **split = malloc(sizeof(char *) * (size + 1));
	int i = 0, j = 0;
	char *start;
	char quote;

	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
		{
			start = &cmd[i];
			while (cmd[i] && cmd[i] == ' ')
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		if (cmd[i] == '\0')
			break;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			start = &cmd[i];
			quote = cmd[i++];
			while (cmd[i] && cmd[i] != quote)
				i++;
			if (cmd[i] == quote)
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		else if (cmd[i] == '$')
		{
			start = &cmd[i];
			i++;
			while (cmd[i] && can_continue(cmd[i]))
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		else
		{
			start = &cmd[i];
			while (cmd[i] && can_continue(cmd[i]))
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
		while (cmd[i] && cmd[i] == ' ')
		{
			start = &cmd[i];
			while (cmd[i] && cmd[i] == ' ')
				i++;
			split[j++] = ft_strndup(start, i - (start - cmd));
		}
	}
	split[j] = NULL;
	free(cmd);
	cmd = NULL;
	return (split);
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
echo "'$"             |
echo "$"              | Arrumei.
echo "'"$USER"'"      | Arrumei.
echo "'$USER'"        |
echo $1a              | Arrumei.
echo $US"ER"          | Arrumei.
echo $US'ER'          | Arrumei.
echo "$USER '' $USER" | Arrumei.
*/
