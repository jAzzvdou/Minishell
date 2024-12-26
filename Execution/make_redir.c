#include "../Include/minishell.h"

void	set_redir(t_main *main, t_tree *tree)
{
	t_type	type;

	type = tree->left->type;
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
		set_redir(main, tree->left);
	type = tree->type;
	if ((type == OUTPUT || type == APPEND)
		&& (tree->left->fd != -1 || !last_status(-1)))
	{
		outfile(tree);
		dup_fd(tree, STDOUT_FILENO);
	}
	else if (tree->left->fd == -1)
		tree->fd = -1;
	else if ((type == INPUT || type == HEREDOC)
		&& (tree->left->fd != -1 || !last_status(-1)))
	{
		infile(tree);
		dup_fd(tree, STDIN_FILENO);
		if (tree->type == HEREDOC)
			unlink(tree->right->exe->first->cmd);
	}
}

void	dup_and_close(const int *tmp)
{
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[1]);
	dup2(tmp[0], STDIN_FILENO);
	close(tmp[0]);
}

void	safe_fd(const int *tmp, int tree_fd, int to_close)
{
	static int	open_fd[3];

	if (!to_close)
	{
		open_fd[0] = tmp[0];
		open_fd[1] = tmp[1];
		open_fd[2] = tree_fd;
	}
	else
	{
		close(open_fd[0]);
		close(open_fd[1]);
		close(open_fd[2]);
	}
}

void	make_redir(t_main *main, t_tree *tree)
{
	const int	tmp[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	if (!tree->fd)
		set_redir(main, tree);
	if (last_status(-1) || tree->fd == -1)
	{
		dup_and_close(tmp);
		return ;
	}
	safe_fd(tmp, tree->fd, 0);
	exec(main, tree->left);
	dup_and_close(tmp);
}
