/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:24:15 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/02 13:56:17 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	make_roots(t_tree *tree, t_tokens *tokens, t_node *node)
{
	t_tokens	*left;
	t_tokens	*right;

	if (!tree || !tokens || !node)
		return (0);
	right = get_right(tokens, node);
	left = get_left(tokens, node);
	tree->type = right->first->type;
	right = remove_last(right);
	if (is_redir(tree->type) && need_transfer(right))
	{
		left = get_from_right(left, right);
		right = send_to_left(right);
	}
	tree->left = build_tree(left);
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
	tree->fd = 0;
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
