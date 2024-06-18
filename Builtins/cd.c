/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:41:22 by bruno             #+#    #+#             */
/*   Updated: 2024/06/18 13:03:54 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char    *env_value(t_env *env, const char *name)
{
    while (env) {
        if (strcmp(env->name, name) == 0)
            return env->value;
        env = env->next;
    }
    return (NULL);
}

void    update_env(t_env **env, const char *name, const char *value)
{
    t_env   *tmp;
    char    *line;

    tmp = *env;
    while (tmp) {
        if (strcmp(tmp->name, name) == 0)
        {
            free(tmp->value);
            tmp->value = strdup(value);
            free(tmp->line);
            tmp->line = ft_strjoin(name, "=");
            tmp->line = ft_strjoin(tmp->line, value);
            return;
        }
        tmp = tmp->next;
    }
    line = ft_strjoin(name, "=");
    line = ft_strjoin(line, value);
    add_env(env, line, 1);
    free(line);
}

int cd_cmd(t_main *main, char **token) 
{
    if (token[1] && token[2]) {
        printf("cd: too many arguments\n");
        return 1;
    }

    if (!token[1] || token[1][0] == '\0' || strcmp(token[1], "~") == 0) {
        if (handle_home(main)) 
            return 1;
    } else if (token[1][0] == '~') {
        if (handle_tilde(main, token[1])) 
            return 1;
    } else if (strcmp(token[1], "-") == 0) {
        if (handle_oldpwd(main)) 
            return 1;
    } else {
        if (handle_path(token[1])) 
            return 1;
    }

    update_pwd_oldpwd(main);

    return 0;
}