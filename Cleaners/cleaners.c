/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:11 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/20 14:20:49 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_env_util(t_env *node)
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
	free(node);
	//node = NULL;
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
		free_env_util(aux);
	}
	*env = NULL;
}

void	free_nodes(t_node *node)
{
	t_node	*aux;

	if (!node)
		return ;
	while (node)
	{
		aux = node;
		node = node->next;
		if (aux->cmd)
		{
			free(aux->cmd);
			aux->cmd = NULL;
		}
		free(aux);
		aux = NULL;
	}
}

void	free_tokens2(t_tokens *tokens)
{
	t_node	*current_node;
	t_node	*next_node;

	if (!tokens)
		return ;
	current_node = tokens->first;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->cmd)
		{
			free(current_node->cmd);
			current_node->cmd = NULL;
		}
		free(current_node);
		current_node = NULL;
		current_node = next_node;
	}
	free(tokens);
	tokens = NULL;
}

void	free_tokens(t_tokens **tokens)
{
	if (!*tokens)
		return ;
	free_nodes((*tokens)->first);
	(*tokens)->first = NULL;
	(*tokens)->last = NULL;
	free(*tokens);
	*tokens = NULL;
}
