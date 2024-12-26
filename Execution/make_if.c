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
