/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:14:45 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/23 23:26:37 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

void	debug(void)
{
        int     start;
        static int      i;

        start = 0;
        i = start + i + 1;
        printf(YELLOW"Debug %d.\n"RESET, i);
}

void    print_tokens(t_tokens *tokens)
{
        t_node  *nodes;

        if (!tokens)
                return ;
        nodes = tokens->first;
        while (nodes)
        {
                printf("token: %s | type: %d\n", nodes->cmd, nodes->type);
                printf("\n");
                nodes = nodes->next;
        }
}

void    revprint_tokens(t_tokens *tokens)
{
        t_node  *nodes;

        nodes = tokens->last;
        while (nodes)
        {
                printf("token: %s | type: %d\n", nodes->cmd, nodes->type);
                printf("\n");
                nodes = nodes->prev;
        }
}

void	print_tree(t_tree *tree, int level)
{
	t_tree	*tmp;

	if (!tree)
		return ;
	tmp = tree;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("Node Type: %d\n", tmp->type);
	if (tmp->exe)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		print_tokens(tmp->exe);
	}
	if (tmp->left)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Left:\n");
		print_tree(tmp->left, level + 1);
	}
	if (tmp->right)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Right:\n");
		print_tree(tmp->right, level + 1);
	}
}
