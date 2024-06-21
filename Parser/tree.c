/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:39 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/21 00:42:30 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*split_tokens(t_tokens *tokens, t_node *node)
{
	t_node		*tmp;
	t_tokens	*right;

	if (!tokens || !node)
		return (NULL);
	right = start_tokens();
	tmp = tokens->last;
	while (tmp && tmp != node)
	{
		//| Adicionar no começo e tirar do final.
		tmp = tmp->prev;
	}
	return (right);
}

//| Estamos lendo os tokens de trás para frente.
int	make_roots(t_tree *tree, t_tokens *tokens, t_node *node)
{
	t_tokens	*right; // vai ser toda a parte da direita do node.

	if (!tree || !tokens || !node)
		return (0);
	right = split_tokens(tokens, node); //| Função que vai splitar o tokens em esquerda e direita.
		  //| A função vai retornar a parte da direita do node.
	tree->type = tokens->last->type; //| O tipo do node vai ser o tipo do último token.
					 //| (AND, OR, PIPE, REDIR ou CMD)
	//| Aqui a gente tem que tirar esse último node da lista de tokens.
	//| Se o tipo do tree->type for um REDIR, a gente tem que fazer um tratamento especial.
	tree->left = build_tree(tokens);
	tree->right = build_tree(right);
	return (1);
}

//| Procurar por ANDs e ORs.
t_node	*is_type1(t_node *last)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

//| Procurar por PIPEs.
t_node  *is_type2(t_node *last)
{
        t_node  *tmp;

        tmp = last;
        while (tmp)
        {
                if (tmp->type == PIPE)
                        return (tmp);
                tmp = tmp->prev;
        }
        return (NULL);
}

//| Procurar por REDIRs.
t_node  *is_type3(t_node *last)
{
        t_node  *tmp;

        tmp = last;
        while (tmp)
        {
                if (tmp->type == INPUT || tmp->type == OUTPUT
			|| tmp->type == APPEND || tmp->type == HEREDOC)
                        return (tmp);
                tmp = tmp->prev;
        }
        return (NULL);
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
	search_priority(tree, tokens);
	return (tree);
}
