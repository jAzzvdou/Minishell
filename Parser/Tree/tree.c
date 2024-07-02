/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:39 by jazevedo          #+#    #+#             */
/*   Updated: 2024/07/01 23:55:20 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	make_roots(t_tree *tree, t_tokens *tokens, t_node *node)
{
	t_tokens	*right;

	if (!tree || !tokens || !node)
		return (0);
	right = split_tokens(tokens, node);
	if (!right)
		return (-1);
	tree->type = tokens->last->type;
	remove_last_node(tokens);
	if (tree->type == INPUT || tree->type == OUTPUT
		|| tree->type == APPEND || tree->type == HEREDOC)
		transfer_nodes(tokens, right);
	tree->left = build_tree(tokens);
	tree->right = build_tree(right);
	return (1);
}

void	search_priority(t_tree *tree, t_tokens *tokens)
{
	if (make_roots(tree, tokens, is_type1(tokens->last)))
		return ;
	if (make_roots(tree, tokens, is_type2(tokens->last)))
		return ;
	if (make_roots(tree, tokens, is_type3(tokens->last)))
		return ;
	if (tokens->last && tokens->last->type == BLOCK)
		tree->type = BLOCK;
	else
		tree->type = CMD;
	tree->exe = tokens;
}

t_tree	*start_tree(void)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->exe = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_tree	*build_tree(t_tokens *tokens)
{
	t_tree	*tree;

	tree = start_tree();
	if (!tree)
		return (NULL);
	search_priority(tree, tokens);
	return (tree);
}
