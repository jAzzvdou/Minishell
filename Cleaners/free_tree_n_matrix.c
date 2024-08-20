/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree_n_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:04:56 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/20 14:07:33 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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
