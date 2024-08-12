/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:11:07 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/12 18:54:35 by jazevedo         ###   ########.fr       */
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

char	*change_var(t_main *main, char *var)
{
	if (var[0] == '\"')
	{
		var = ft_strndup(var + 1, ft_strlen(var) - 2);
		if (!var)
			var = ft_strdup("\0");
		return (expand_bonus(main, var));
	}
	if (var[0] == '$' && var[1])
	{
		var = ft_strndup(var + 1, ft_strlen(var) - 1);
		var = find_var(main, var);
	}
	return (var);
}
