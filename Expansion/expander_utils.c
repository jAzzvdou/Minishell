#include "../Include/minishell.h"

char	*merge_str(char *s1, char *s2)
{
	char	*merged;

	merged = my_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (merged);
}

char	*merge_special(char *s, char *var, int option)
{
	char	*special;
	char	*leftover;

	if (!option)
		special = my_strdup(s);
	else
		special = s;
	leftover = my_strndup(var + 1, my_strlen(var) - 1);
	return (merge_str(special, leftover));
}

char	*special_cases(char *var)
{
	char	*tmp;

	tmp = NULL;
	if (var[0] == '0')
	{
		if (var[1])
			tmp = merge_special("minichad", var, 0);
		else
			tmp = my_strdup("minichad");
	}
	else if (var[0] == '?')
	{
		if (var[1])
			tmp = merge_special(my_itoa(last_status(-1)), var, 1);
		else
			tmp = my_itoa(last_status(-1));
	}
	else if (var[0] == '-')
	{
		if (var[1])
			tmp = merge_special("himBHs", var, 0);
		else
			tmp = my_strdup("himBHs");
	}
	return (tmp);
}

char	*find_var(t_main *main, char *var)
{
	char	*tmp;
	t_env	*env;

	tmp = NULL;
	if (!is_valid(var[0]))
	{
		if (is_number(var[0]) && var[0] != '0')
			tmp = my_strndup(var + 1, my_strlen(var) - 1);
	}
	if (var[0] == '?' || var[0] == '0' || var[0] == '-')
		tmp = special_cases(var);
	env = main->env;
	while (env && !tmp)
	{
		if (!my_strcmp(var, env->name))
			tmp = my_strdup(env->value);
		env = env->next;
	}
	free(var);
	var = NULL;
	return (tmp);
}

char	*change_var(t_main *main, char *var)
{
	if (var[0] == '\"')
	{
		var = my_strndup(var + 1, my_strlen(var) - 2);
		if (!var)
			var = my_strdup("\0");
		return (expand_bonus(main, var));
	}
	if (var[0] == '$')
	{
		var = my_strndup(var + 1, my_strlen(var) - 1);
		if (!var)
			return (my_strdup("\0"));
		var = find_var(main, var);
	}
	return (var);
}
