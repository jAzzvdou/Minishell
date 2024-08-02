/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:36:53 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/02 17:35:17 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*get_env_value(t_env *env, const char *name)
{
    while (env)
    {
        if (!ft_strcmp(env->name, name))
            return (env->value);
        env = env->next;
    }
    return ("");
}

void	handle_quotes(const char **start, int *doubles, int *singles)
{
	if (**start == '\"' && !*singles)
	{
		*doubles = !*doubles;
		(*start)++;
	}
	else if (**start == '\'' && !*doubles)
	{
		*singles = !*singles;
		(*start)++;
	}
}

int	expand_var(t_main *main, char **expanded, const char **start)
{
	const char *end = *start + 1;
	while (isalnum(*end) || *end == '_')
		end++;
	char *name = strndup(*start + 1, end - *start - 1);
	char *value = get_env_value(main->env, name);
	if (!strncmp(*start, "$0", 2))
		value = "minichad";
	strcat(*expanded, value);
	free(name);
	name = NULL;
	*start = end - 1;
	return (1);
}

char	*expand_variables(t_main *main, const char *cmd)
{
	int singles = 0;
	int doubles = 0;
	char *expanded = calloc(INT_MAX, 1); //| <- Gambiarra sinistra.
	while (*cmd)
	{
		handle_quotes(&cmd, &doubles, &singles);
		if (*cmd == '$' && !singles)
		{
			if (!expand_var(main, &expanded, &cmd)) 
			{
				free(expanded);
				expanded = NULL;
				return strdup("");
			}
		}
		else
			strncat(expanded, cmd, 1);
		cmd++;
	}
	return expanded;
}

void	expand_tokens(t_main *main, t_tokens *tokens)
{
	char	*expanded_cmd;
	t_node	*tmp;

	tmp = tokens->first;
	while (tmp)
	{
		if (tmp->cmd)
		{
			expanded_cmd = expand_variables(main, tmp->cmd);
			if (expanded_cmd)
			{
				free(tmp->cmd);
				tmp->cmd = expanded_cmd;
			}
		}
		tmp = tmp->next;
	}
}

t_tokens	*expander(t_main *main, t_tokens *tokens)
{
	//t_tokens	*tmp;
	t_tokens	*expanded;

	expanded = wildcard(tokens);
	expand_tokens(main, expanded);
	//expanded = variables(main, tmp);
	//| Free em tokens.
	//| Free em tmp.
	return (expanded);
}
