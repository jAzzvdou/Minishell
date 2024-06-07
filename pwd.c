#include "minishell.h"

void	start_pwd(t_main *main)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	main->pwd = ft_strdup(cwd);
	//main->pwd = get_oldpwd(main);
}
