#include "../Include/minishell.h"

void	set_value(t_env *new, char *line)
{
	char	*join;

	if (!my_strcmp(new->name, "SHLVL"))
	{
		new->value = my_itoa(my_atoll(my_strchr(line, '=') + 1) + 1);
		join = my_strndup(line, my_strchr(line, '=') - line + 1);
		new->line = my_strjoin(join, new->value);
		free(join);
	}
	else
	{
		new->value = my_strdup(my_strchr(line, '=') + 1);
		new->line = my_strdup(line);
	}
}

void	add_env(t_env **env, char *line, int declare_x)
{
	t_env	*new;
	t_env	*tmp;

	if (!line)
		return ;
	new = (t_env *)malloc(sizeof(t_env));
	new->declare_x = declare_x;
	new->name = my_strndup(line, my_strchr(line, '=') - line);
	set_value(new, line);
	new->next = NULL;
	if (!(*env))
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	start_env(t_main *main, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		add_env(&main->env, envp[i], 1);
}

void	env_cmd(t_main *main, char **token)
{
	int		i;
	t_env	*env;

	i = 0;
	while (token[i])
	{
		if (!my_strcmp(token[i], "env"))
			i++;
		else
		{
			error_env(token[i]);
			last_status(127);
			return ;
		}
	}
	env = main->env;
	while (env)
	{
		if (env->declare_x)
			printf(WHITE"%s\n"RESET, env->line);
		env = env->next;
	}
	last_status(0);
}
