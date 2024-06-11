#include "minishell.h"

void	start_pwd(t_main *main)
{
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	main->pwd = ft_strdup(cwd);
	main->old_pwd = ft_strdup(cwd);
}
