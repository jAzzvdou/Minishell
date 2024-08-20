/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:20:43 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/20 10:14:23 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	is_valid_identifier(char *token)
{
	int	is_valid;

	if (token[0] == '_')
		return (1);
	is_valid = ft_isalpha(token[0]);
	return (is_valid);
}

void	up_env_var(t_env *env_var, char *equals_sign, char *token)
{
	free(env_var->value);
	env_var->value = ft_strdup(equals_sign + 1);
	free(env_var->line);
	env_var->line = ft_strdup(token);
}

void	add_new_env_var(t_main *main, char *token, char *equals_sign)
{
	char	*empty_value_line;

	if (*(equals_sign + 1) == '\0')
	{
		empty_value_line = ft_strjoin(token, "");
		add_env(&main->env, empty_value_line, 1);
		free(empty_value_line);
	}
	else
		add_env(&main->env, token, 1);
}

void	update_or_add_env_var(t_main *main, char *name,
	char *equals_sign, char *token)
{
	t_env	*env_var;

	env_var = main->env;
	while (env_var)
	{
		if (!ft_strcmp(env_var->name, name))
		{
			up_env_var(env_var, equals_sign, token);
			free(name);
			return ;
		}
		env_var = env_var->next;
	}
	free(name);
	add_new_env_var(main, token, equals_sign);
}

void	handle_equal_sign(t_main *main, char *token)
{
	char	*name;
	char	*equals_sign;

	equals_sign = ft_strchr(token, '=');
	if (equals_sign)
	{
		name = ft_strndup(token, equals_sign - token);
		update_or_add_env_var(main, name, equals_sign, token);
	}
	else
	{
		handle_no_equals_error(token);
	}
}
