#include "../Include/minishell.h"

void	dup_fd(t_tree *tree, int fd)
{
	if (tree->fd != -1)
	{
		dup2(tree->fd, fd);
		close(tree->fd);
	}
}

void	verify_permissions(char *file)
{
	if (last_status(-1))
		return ;
	if (!access(file, F_OK) && access(file, W_OK | R_OK))
	{
		err(GREY"minichad: Permission denied\n"WHITE);
		last_status(1);
	}
	else if (access(file, F_OK))
	{
		err(GREY"minichad: No such file of directory\n"WHITE);
		last_status(1);
	}
}

void	infile(t_tree *tree)
{
	char	*file;

	file = tree->right->exe->first->cmd;
	tree->fd = open(file, O_RDONLY);
	if (tree->fd == -1 && last_status(-1))
		last_status(0);
	verify_permissions(file);
}

void	outfile(t_tree *tree)
{
	char	*file;

	file = tree->right->exe->first->cmd;
	if (tree->type == OUTPUT)
		tree->fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 00700);
	else if (tree->type == APPEND)
		tree->fd = open(file, O_CREAT | O_RDWR | O_APPEND, 00700);
	if ((tree->fd == -1) && last_status(-1))
		last_status(0);
	verify_permissions(file);
}
