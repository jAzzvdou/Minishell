/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:39 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/20 19:49:51 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_tokens(t_tree *tree, t_tokens *tokens, t_node *node)
{
	t_tokens	*right; // vai ser toda a parte da direita do node.

	if (!tree || !tokens || !node)
		return (0);
	right = ; //| Função que vai splitar o tokens em esquerda e direita.
		  //| A função vai retornar a parte da direita do node.
	tree->type = tokens->last->type; //| O tipo do node vai ser o tipo do último token.
					 //| (AND, OR, PIPE, REDIR ou CMD)
	//| Aqui a gente tem que tirar esse último node da lista de tokens.
	//| Se o tipo do tree->type for um REDIR, a gente tem que fazer um tratamento especial.
	tree->left = build_tree(tokens);
	tree->right = build_tree(right);
}

t_node	*is_type(t_node *last, e_type type1, e_type type2)
{
	t_node	*tmp;

	tmp = last;
	if (!type2)
		type2 = type1;
	while (tmp)
	{
		if (tmp->type == type1 || tmp->type == type2)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

void	make_roots(t_tree *tree, t_tokens *tokens)
{
	if (split_tokens(tree, tokens, is_type(tokens->last, AND, OR)))
		return ;
	if (split_tokens(tree, tokens, is_type(tokens->last, PIPE, NULL)))
		return ;
	if (split_tokens(tree, tokens, is_type(tokens->last, REDIR, NULL)))
		return ;
	tree->type = CMD;
	tree->exe = tokens;
}

t_tree	*start_tree(void)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_tree	build_tree(t_tokens *tokens)
{
	t_tree	*tree;

	tree = start_tree();
	if (!tree)
		return (NULL);
	make_roots(tree, tokens);
	return (tree);
}
