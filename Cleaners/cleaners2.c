/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:17:19 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/29 14:18:45 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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
