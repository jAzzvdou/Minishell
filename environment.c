#include "minishell.h"

void	start_pwd(t_main *main)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	main->pwd = ft_strdup(cwd);
	//main->pwd = get_oldpwd(main);
}

//--------------------| TESTES |--------------------//
void    add_env(t_env **env, char *line)
{
        t_env   *new;

	new = malloc(sizeof(t_env));
	new->name = ft_strndup(line, ft_strchr(line, '=') - line);
	new->value = ft_strdup(ft_strchr(line, '=') + 1);
	new->line = ft_strdup(line);
	new->next = NULL;
}

void    start_env(t_main *main, char **envp)
{
        int     i;

        i = -1;
        while (envp[++i])
                add_env(&main->env, envp[i]);
}
