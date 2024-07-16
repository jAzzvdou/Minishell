/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:40:07 by jazevedo          #+#    #+#             */
/*   Updated: 2024/07/10 14:00:50 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	print_type(e_type type)
{
	if (type == CMD)
		printf("type %d = CMD\n", type);
	else if (type == BLOCK)
		printf("type %d = BLOCK\n", type);
	else if (type == HEREDOC)
		printf("type %d = HEREDOC\n", type);
	else if (type == OR)
		printf("type %d = OR\n", type);
	else if (type == AND)
		printf("type %d = AND\n", type);
	else if (type == PIPE)
		printf("type %d = PIPE\n", type);
	else if (type == INPUT)
		printf("type %d = INPUT\n", type);
	else if (type == OUTPUT)
		printf("type %d = OUTPUT\n", type);
	else if (type == APPEND)
		printf("type %d = APPEND\n", type);
}

void	exec(t_main *main, t_tree *tree)
{
	print_type(tree->type);
	if (tree->type == AND || tree->type == OR)
		make_if(main, tree);
	else if (tree->type == PIPE)
		make_pipe(main, tree);
	else if (tree->type == INPUT || tree->type == OUTPUT
		|| tree->type == HEREDOC || tree->type == APPEND)
		make_redir(main, tree); //| LIDAR COM ISSO (FAZER OS REDIRECTS);*/
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
