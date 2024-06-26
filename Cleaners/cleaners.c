/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:39:16 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/24 16:20:08 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
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
		free(aux->name);
		aux->name = NULL;
		free(aux->value);
		aux->value = NULL;
		free(aux->line);
		aux->line = NULL;
		free(aux);
		aux = NULL;
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
		free(aux->cmd);
		aux->cmd = NULL;
		free(aux);
		aux = NULL;
	}
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

void	free_tree(t_tree **tree)
{
	if (!*tree)
		return ;
	free_tree(&(*tree)->left);
	free_tree(&(*tree)->right);
	free(*tree);
	*tree = NULL;
}

void	free_everything(t_main *main)
{
	free(main->pwd);
	main->pwd = NULL;
	free(main->old_pwd);
	main->old_pwd = NULL;
	free_env(&main->env);
	free_tokens(&main->tokens);
	free_tree(&main->tree);
	rl_clear_history();
}
