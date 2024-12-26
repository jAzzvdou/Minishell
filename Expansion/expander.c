#include "../Include/minishell.h"

char	*expand_bonus(t_main *main, char *cmd)
{
	int		i;
	char	*tmp;
	char	**splited;

	splited = split_bonus(cmd);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '$')
		{
			tmp = splited[i];
			splited[i] = change_var(main, tmp);
			free(tmp);
		}
		if (!splited[i])
			splited[i] = my_strdup("\0");
		i++;
	}
	return (concatenator(splited));
}

char	*expand(t_main *main, char *cmd)
{
	int		i;
	char	*tmp;
	char	**splited;

	splited = split_variable(cmd);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\'')
		{
			tmp = splited[i];
			splited[i] = my_strndup(tmp + 1, my_strlen(tmp) - 2);
			free(tmp);
		}
		else
		{
			tmp = splited[i];
			splited[i] = change_var(main, tmp);
			free(tmp);
		}
		if (!splited[i])
			splited[i] = my_strdup("\0");
		i++;
	}
	return (tmp = concatenator(splited), tmp);
}

char	*not_expand(char *cmd)
{
	int		i;
	char	*tmp;
	char	**splited;

	splited = split_variable(cmd);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\"' || splited[i][0] == '\'')
		{
			tmp = splited[i];
			splited[i] = my_strndup(tmp + 1, my_strlen(tmp) - 2);
			free(tmp);
		}
		if (!splited[i])
			splited[i] = my_strdup("\0");
		i++;
	}
	tmp = concatenator(splited);
	return (tmp);
}

t_tokens	*variables(t_main *main, t_tokens *tokens)
{
	t_node		*tmp;
	t_tokens	*expanded;

	expanded = start_tokens();
	tmp = tokens->first;
	while (tmp)
	{
		if (is_var(tmp->cmd) && tmp->type == CMD)
			add_token(expanded, tmp->type, expand(main, tmp->cmd));
		else
			add_token(expanded, tmp->type, not_expand(tmp->cmd));
		tmp = tmp->next;
	}
	free_tokens2(tokens);
	return (expanded);
}

t_tokens	*expander(t_main *main, t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*expanded;

	tmp = wildcard(tokens);
	expanded = variables(main, tmp);
	return (expanded);
}
