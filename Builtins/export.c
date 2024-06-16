/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:39:39 by bruno             #+#    #+#             */
/*   Updated: 2024/06/16 20:24:48 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	swap_nodes(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->line;
	a->line = b->line;
	b->line = tmp;
}

t_env	*alphabetical_env(t_env *tmp)
{
	int 		swapped;
	t_env	*ordered;
	t_env	*current;

	if (!tmp)
		return (NULL);
	ordered = tmp;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = ordered;
		while (current->next)
		{
			if (ft_strcmp(current->line, current->next->line) > 0)
			{
				swap_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (ordered);
}

void    add_without_equal(t_env **env, char *line, int declare_x)
{
        t_env *new;
        t_env *tmp;

        if(!line)
                return ;
        new = (t_env *)malloc(sizeof(t_env));
        new->declare_x = declare_x;
        new->name = ft_strdup(line);
        new->value = NULL;
        new->line = ft_strdup(line);
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

void	export_cmd(t_main *main, char **token)
{
	int		i;
	t_env 	*tmp;
	t_env 	*env_var;
	char	*equals_sign;
	char	*name;

	tmp = main->env;
	if (!token[1])
	{
		t_env *sorted_env = alphabetical_env(tmp);
		while (sorted_env)
		{
			printf("declare -x %s\n", sorted_env->line);
			sorted_env = sorted_env->next;
		}
		return;
	}

	i = 1;
	while (token[i])
	{
		printf("Processing token: %s\n", token[i]);
		if (!(ft_isalpha(token[i][0])))
		{
			printf("minishell: export: '%s': not a valid identifier\n", token[i]);
			i++;
			continue;
		}

		equals_sign = ft_strchr(token[i], '=');
		if (equals_sign)
		{
			name = ft_strndup(token[i], equals_sign - token[i]);

			// Verificar se a variável já existe
			env_var = tmp;
			while (env_var)
			{
				if (strcmp(env_var->name, name) == 0)
				{
					// Atualizar valor da variável existente
					free(env_var->value);
					env_var->value = ft_strdup(equals_sign + 1);
					free(env_var->line);
					env_var->line = ft_strdup(token[i]);
					free(name);
					break;
				}
				env_var = env_var->next;
			}

			// Se a variável não existir, adicionar nova variável
			if (!env_var)
			{
				if (*(equals_sign + 1) == '\0')
				{
					char *empty_value_line = ft_strjoin(token[i], "\"\"");
					printf("Adding to env with value: %s\n", empty_value_line);
					add_env(&main->env, empty_value_line, 1);
					free(empty_value_line);
				}
				else
				{
					printf("Adding to env with value: %s\n", token[i]);
					add_env(&main->env, token[i], 1);
				}
			}
		}
		else
		{
			printf("Ignoring token without '=': %s\n", token[i]);
			add_without_equal(&main->env, token[i], 0);
		}
		i++;
	}
	printf("Finished processing export command\n");
}

