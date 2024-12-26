#include "../Include/minishell.h"

int	env_size(t_env *env)
{
	int		count;
	t_env	*list;

	list = env;
	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

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
			re_exec(main, get_block(tree->exe));
		else
			controller(main, token_to_args(tree->exe));
	}
}
