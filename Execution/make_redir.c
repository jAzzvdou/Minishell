
#include "../Include/minishell.h"

void	set_redir(t_main *main, t_tree *tree)
{
	e_num	*type;

	type = tree->left->type;
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
		set_redir(main, tree->left); //| Caso o LEFT seja REDIR também.
	type = tree->type;
	if ((type == OUTPUT || type == APPEND)
		&& (tree->left->fd != -1 || !last_status(-1))) //| OUTFILE caso o seput dos REDIRs esteja certo.
	{
		outfile(main, tree); //| FAZER OUTPUT E APPEND.
		if (tree->fd != -1)
		{
			dup2(tree->fd, STDOUT_FILENO);
			close(tree->fd);
		}
	}
	//| CASO Tree->left->fd == -1, tem que setar o atual para -1.
	else if (tree->left->fd == -1) //| DEU ERRADO.
		tree->fd = -1;
	else if ((type == INPUT || type == HEREDOC)
		 && (tree->left->fd != -1 || !last_status(-1)))
	{
		infile(main, tree); // FAZER INPUT E HEREDOC.
		if (tree->fd != -1)
		{
			dup2(tree->fd, STDIN_FILENO);
			close(tree->fd);
		}
		if (tree->type == HEREDOC)
			unlink(tree->right->exe->first->cmd);
	}
}

void	make_redir(t_main *main, t_tree *tree)
{
	int		in;
	int		out;
	static int	backup[3];

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (!tree->fd) //| Caso não tenha FD ainda seta os FDs dos nodes da árvore.
		set_redir(main, tree);
	if (tree->fd != -1 || !last_status(-1))
	{
		backup[0] = in;
		backup[1] = out;
		backup[2] = tree->fd;
		exec(main, tree->left); //| DEU CERTO ENTÃO EXECUTA.
	}
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
}
