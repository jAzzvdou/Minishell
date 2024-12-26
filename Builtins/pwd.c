#include "../Include/minishell.h"

void	start_pwd(t_main *main)
{
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	main->pwd = my_strdup(cwd);
	main->old_pwd = my_strdup(cwd);
}
