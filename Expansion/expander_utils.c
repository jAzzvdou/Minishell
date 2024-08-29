/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:11:07 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/29 15:05:25 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*merge_str(char *s1, char *s2)
{
	char	*merged;

	merged = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (merged);
}

char	*merge_special(char *s, char *var, int option)
{
	char	*special;
	char	*leftover;

	if (!option)
		special = ft_strdup(s);
	else
		special = s;
	leftover = ft_strndup(var + 1, ft_strlen(var) - 1);
	return (merge_str(special, leftover));
}

char	*special_cases(char *var)
{
	char	*tmp;

	tmp = NULL;
	if (var[0] == '0')
	{
		if (var[1])
			tmp = merge_special("minichad", var, 0);
		else
			tmp = ft_strdup("minichad");
	}
	else if (var[0] == '?')
	{
		if (var[1])
			tmp = merge_special(ft_itoa(last_status(-1)), var, 1);
		else
			tmp = ft_itoa(last_status(-1));
	}
	else if (var[0] == '-')
	{
		if (var[1])
			tmp = merge_special("himBHs", var, 0);
		else
			tmp = ft_strdup("himBHs");
	}
	return (tmp);
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
	if (var[0] == '?' || var[0] == '0' || var[0] == '-')
		tmp = special_cases(var);
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
	if (var[0] == '$')
	{
		var = ft_strndup(var + 1, ft_strlen(var) - 1);
		if (!var)
			return (ft_strdup("\0"));
		var = find_var(main, var);
	}
	return (var);
}
