/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:12 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/19 16:10:49 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	infile(t_tree *tree)
{
	char	*file;

	file = tree->right->exe->first->cmd;
	tree->fd = open(file, O_RDONLY);
	if (!access(file, F_OK) && access(file, W_OK | R_OK))
	{
		err(GREY"minichad: Permission denied\n"RESET);
		last_status(1);
	}
	else if (access(file, F_OK))
	{
		if (g_status == 130)
			last_status(130);
		else
		{
			err(GREY"minichad: No such file or directory\n"RESET);
			last_status(1);
		}
	}
}

void	outfile(t_tree *tree)
{
	char	*file;

	file = tree->right->exe->first->cmd;
	if (tree->type == OUTPUT)
		tree->fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 00700);
	else if (tree->type == APPEND)
		tree->fd = open(file, O_CREAT | O_RDWR | O_APPEND, 00700);
	if (!access(file, F_OK) && access(file, W_OK | R_OK))
	{
		err(GREY"minichad: Permission denied\n"RESET);
		last_status(1);
	}
	else if (access(file, F_OK))
	{
		err(GREY"minichad: No such file or directory\n"RESET);
		last_status(1);
	}
}

void	dup_close(t_tree *tree, int std)
{
	dup2(tree->fd, std);
	close(tree->fd);
}

void	set_redir(t_main *main, t_tree *tree)
{
	t_type	type;

	type = tree->left->type;
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
		set_redir(main, tree->left);
	type = tree->type;
	if ((type == OUTPUT || type == APPEND) && !last_status(-1))
	{
		outfile(tree);
		if (tree->fd >= 0)
			dup_close(tree, STDOUT_FILENO);
	}
	else if ((type == INPUT || type == HEREDOC) && !last_status(-1))
	{
		infile(tree);
		if (tree->fd >= 0)
			dup_close(tree, STDIN_FILENO);
	}
}

void	make_redir(t_main *main, t_tree *tree)
{
	int		in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	set_redir(main, tree);
	if (tree->fd >= 0 || !last_status(-1))
	{
		exec(main, tree->left);
		if (tree->type == HEREDOC)
			unlink(tree->right->exe->first->cmd);
	}
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
}
