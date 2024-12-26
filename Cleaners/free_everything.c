#include "../Include/minishell.h"

void	free_everything(t_main *main)
{
	if (main->pwd)
	{
		free(main->pwd);
		main->pwd = NULL;
	}
	if (main->old_pwd)
	{
		free(main->old_pwd);
		main->old_pwd = NULL;
	}
	free_env(&main->env);
	free_tree2(main->tree);
	rl_clear_history();
}
