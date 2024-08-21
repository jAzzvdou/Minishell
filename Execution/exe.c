/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:55 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/19 17:23:03 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	exec(t_main *main, t_tree *tree)
{
	if (tree->type == AND || tree->type == OR)
		make_if(main, tree);
	else if (tree->type == PIPE)
		make_pipe(main, tree);
	else if (tree->type == INPUT || tree->type == OUTPUT
		|| tree->type == HEREDOC || tree->type == APPEND)
		make_redir(main, tree);
	else if (tree->left)
		exec(main, tree->left);
	else if (tree->right)
		exec(main, tree->right);
	else if (tree->exe && tree->exe->first)
	{
		if (tree->type == BLOCK)
			re_exec(main, tree->exe->first->cmd);
		else
			controller(main, token_to_args(tree->exe));
	}
}
