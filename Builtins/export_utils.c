#include "../Include/minishell.h"

void	handle_no_args(t_env *env)
{
	t_env	*sorted_env;

	sorted_env = alphabetical_env(env);
	while (sorted_env)
	{
		printf("declare -x %s\n", sorted_env->line);
		sorted_env = sorted_env->next;
	}
}

int	is_valid_identifier(char *token)
{
	int	is_valid;

	if (token[0] == '_')
		return (1);
	is_valid = my_isalpha(token[0]);
	return (is_valid);
}

void	up_env_var(t_env *env_var, char *equals_sign, char *token)
{
	free(env_var->value);
	env_var->value = my_strdup(equals_sign + 1);
	free(env_var->line);
	env_var->line = my_strdup(token);
}

void	add_new_env_var(t_main *main, char *token, char *equals_sign)
{
	char	*empty_value_line;

	if (*(equals_sign + 1) == '\0')
	{
		empty_value_line = my_strjoin(token, "");
		add_env(&main->env, empty_value_line, 1);
		free(empty_value_line);
	}
	else
		add_env(&main->env, token, 1);
}

void	handle_equal_sign(t_main *main, char *token)
{
	char	*name;
	char	*equals_sign;
	t_env	*env_var;

	equals_sign = my_strchr(token, '=');
	env_var = main->env;
	if (equals_sign)
	{
		name = my_strndup(token, equals_sign - token);
		while (env_var)
		{
			if (!my_strcmp(env_var->name, name))
			{
				up_env_var(env_var, equals_sign, token);
				free(name);
				return ;
			}
			env_var = env_var->next;
		}
		free(name);
		add_new_env_var(main, token, equals_sign);
	}
	else
		err_equal_sign(token);
}
