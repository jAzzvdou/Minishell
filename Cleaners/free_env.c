/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:43:46 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/13 16:50:49 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_env_fields(t_env *node)
{
	if (node->name)
	{
		free(node->name);
		node->name = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	if (node->line)
	{
		free(node->line);
		node->line = NULL;
	}
}

void	free_env_node_util(t_env *node)
{
	free_env_fields(node);
	free(node);
}

void	free_env(t_env **env)
{
	t_env	*aux;

	if (!*env)
		return ;
	while (*env)
	{
		aux = *env;
		*env = (*env)->next;
		free_env_node_util(aux);
	}
	*env = NULL;
}
