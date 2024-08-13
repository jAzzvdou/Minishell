/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:59:42 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/13 14:00:33 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	update_existing_env_var(t_env *env_var, char *name, char *token)
{
	if (!ft_strcmp(env_var->name, name))
	{
		up_env_var(env_var, ft_strchr(token, '='), token);
		free(name);
	}
}

void	add_env_var_if_not_found(t_main *main, char *name, char *token)
{
	t_env	*env_var;

	env_var = main->env;
	while (env_var)
	{
		if (!ft_strcmp(env_var->name, name))
		{
			free(name);
			return ;
		}
		env_var = env_var->next;
	}
	add_new_env_var(main, token, ft_strchr(token, '='));
	free(name);
}
