/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:11 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/15 12:17:38 by btaveira         ###   ########.fr       */
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
		if (aux->name)
		{
			free(aux->name);
			aux->name = NULL;
		}
		if (aux->value)
		{
			free(aux->value);
			aux->value = NULL;
		}
		if (aux->line)
		{
			free(aux->line);
			aux->line = NULL;
		}
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

void	free_tree2(t_tree *tree)
{
	t_node	*current;
	t_node	*next;

	if (!tree)
		return ;
	free_tree2(tree->left);
	free_tree2(tree->right);
	if (tree->exe)
	{
		current = tree->exe->first;
		while (current)
		{
			next = current->next;
			if (current->cmd)
				free(current->cmd);
			free(current);
			current = next;
		}
		free(tree->exe);
	}
	free(tree);
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
