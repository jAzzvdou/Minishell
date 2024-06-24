/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:39 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/24 15:08:22 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

//| Estamos lendo os tokens de trás para frente.
int	make_roots(t_tree *tree, t_tokens *tokens, t_node *node)
{
	t_tokens	*right; // vai ser toda a parte da direita do node.

	if (!tree || !tokens || !node)
		return (0);
	right = split_tokens(tokens, node); //| Função que vai splitar o tokens em esquerda e direita.
					    //| A função vai retornar a parte da direita do node.
	if (!right)
		return (-1);
	tree->type = tokens->last->type; //| O tipo do node vai ser o tipo do último token.
					 //| (AND, OR, PIPE, REDIR ou CMD)
	//| Aqui a gente tem que tirar esse último node da lista de tokens.
	remove_last_node(tokens);
	//| Se o tipo do tree->type for um REDIR, a gente tem que fazer um tratamento especial.
	if (tree->type == INPUT || tree->type == OUTPUT
		|| tree->type == APPEND || tree->type == HEREDOC)
		transfer_nodes(tokens, right); //| Vamos lidar com isso: echo A > B C D E
					       //| Deve virar isso: echo A C D E > B.
	tree->left = build_tree(tokens);
	tree->right = build_tree(right);
	return (1);
}

//| Função que vai criar os nodes do tree com base na prioridade dos tokens.
void	search_priority(t_tree *tree, t_tokens *tokens)
{
	if (make_roots(tree, tokens, is_type1(tokens->last)))
		return ;
	if (make_roots(tree, tokens, is_type2(tokens->last)))
		return ;
	if (make_roots(tree, tokens, is_type3(tokens->last)))
		return ;
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
