/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:39:39 by bruno             #+#    #+#             */
/*   Updated: 2024/06/11 16:40:27 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void swap_nodes(t_env *a, t_env *b)
{
    char *temp_line = a->line;
    a->line = b->line;
    b->line = temp_line;
}

t_env *ft_alphabetical_env(t_env *temp)
{
    t_env *ordered;
    t_env *current;
    int swapped;

    if (!temp)
        return NULL;

    ordered = temp;
	swapped = 1;
    while (swapped)
    {
        swapped = 0;
        current = ordered;
        while (current->next)
        {
            if (strcmp(current->line, current->next->line) > 0)
            {
                swap_nodes(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
    }
    return ordered;
}

void	export_cmd(t_main *main, char **token)
{
	int		i;
	t_env 	*temp;

	
    temp = main->env;
    if (!token[1])
    {
        t_env *sorted_env = ft_alphabetical_env(temp);
        while (sorted_env)
        {
            printf("declare -x %s\n", sorted_env->line);
            sorted_env = sorted_env->next;
        }
    }
	i = 1;
	while(token[i])
	{
		if(!(ft_isalpha(token[i][0])))
		{
			printf("bash: export: '%s': not a valid identifier\n",token[i]);
			i++;
		}
		if(token[i] && !(ft_strchr(token[i],'=')))
			add_env(&main->env,token[i],0);
		else if(token[i])
			add_env(&main->env,token[i],1);
		i++;
	}
}
