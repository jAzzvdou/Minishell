/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:41:22 by bruno             #+#    #+#             */
/*   Updated: 2024/06/17 09:42:44 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char *env_value(t_env *env, const char *name) {
    while (env) {
        if (strcmp(env->name, name) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

void update_env(t_env **env, const char *name, const char *value) {
    t_env *tmp = *env;
    while (tmp) {
        if (strcmp(tmp->name, name) == 0) {
            free(tmp->value);
            tmp->value = strdup(value);
            free(tmp->line);
            tmp->line = ft_strjoin(name, "=");
            tmp->line = ft_strjoin(tmp->line, value);
            return;
        }
        tmp = tmp->next;
    }
    // Se a variável não existe, adiciona uma nova entrada
    char *line = ft_strjoin(name, "=");
    line = ft_strjoin(line, value);
    add_env(env, line, 1);
    free(line);
}

int cd_cmd(t_main *main, char **token) 
{
    char *path;
    char *new_path;
    char new_pwd[1024];

    if (token[1] && token[2]) {
        printf("cd: too many arguments\n");
        return 1;
    }

    if (!token[1] || token[1][0] == '\0' || strcmp(token[1], "~") == 0) {
        path = env_value(main->env, "HOME");
        if (path == NULL) {
            printf("cd: HOME is not set\n");
            return 1;
        }
        if (chdir(path) != 0) {
            perror("cd");
            return 1;
        }
    } else if (token[1][0] == '~') {
        path = env_value(main->env, "HOME");
        if (path == NULL) {
            printf("cd: HOME is not set\n");
            return 1;
        }
        new_path = ft_strjoin(path, (token[1] + 1));
        if (new_path == NULL) {
            printf("cd: memory allocation error\n");
            return 1;
        }
        if (chdir(new_path) != 0) {
            perror("minishell: cd");
            free(new_path);
            return 1;
        }
        free(new_path);
    } else if (strcmp(token[1], "-") == 0) {
        path = env_value(main->env, "OLDPWD");
        if (path == NULL) {
            printf("cd: OLDPWD is not set\n");
            return 1;
        }
        if (chdir(path) != 0) {
            perror("minishell: cd");
            return 1;
        }
        printf("%s\n", path);
    } else {
        if (chdir(token[1]) != 0) {
            perror("minishell: cd");
            return 1;
        }
    }

    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL) {
        perror("getcwd");
        return 1;
    }

    // Atualiza pwd e old_pwd
    free(main->old_pwd);
    main->old_pwd = main->pwd;
    main->pwd = strdup(new_pwd);

    // Atualiza as variáveis de ambiente
    update_env(&main->env, "OLDPWD", main->old_pwd);
    update_env(&main->env, "PWD", main->pwd);

    //printf("%s\n", main->pwd);

    return 0;
}
