#include "minishell.h"

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

void	env_cmd(t_main *main, char **token)
{
	int	i;
	t_env	*env;

	i = 0;
	while (token[i])
	{
		if (!strcmp(token[i], "env"))
			i++;
		else
		{
			printf(GREY"env: '%s': No such file or directory\n",
				token[i]);
			return ;
		}
	}
	env = main->env;
	while (env)
	{
		printf(WHITE"%s\n"RESET, env->line);
		env = env->next;
	}
}
