/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_if.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:41:50 by jazevedo          #+#    #+#             */
/*   Updated: 2024/07/10 12:42:15 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	make_if(t_main *main, t_tree *tree)
{
	if (tree->type == AND)
	{
		if (tree->left)
			exec(main, tree->left);
		if (last_status(-1) == 0 && tree->right)
			exec(main, tree->right);
	}
	else if (tree->type == OR)
	{
		if (tree->left)
			exec(main, tree->left);
		if (last_status(-1) != 0 && tree->right)
			exec(main, tree->right);
	}
}
