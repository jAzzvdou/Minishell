/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:45 by bruno             #+#    #+#             */
/*   Updated: 2024/06/23 23:36:16 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char    **token_to_args(t_node *first)
{
        int	i;
        char	**args;
        t_node	*node;

        node = first;
        i = 0;
        while (node)
        {
                i++;
                node = node->next;
        }
        args = (char **)malloc(sizeof(char *) * (i + 1));
        i = 0;
        node = first;
        while (node)
        {
                args[i] = ft_strdup(node->cmd);
                i++;
                node = node->next;
        }
        args[i] = NULL;
        return (args);
}

void	controller(t_main *main, char **token)
{
	if (!strcmp(token[0], "exit"))
		exit_cmd(main, token);
	else if (!strcmp(token[0], "env"))
		env_cmd(main, token);
	else if (!strcmp(token[0], "pwd"))
		printf("%s\n", main->pwd);
	else if (!strcmp(token[0], "echo"))
		echo_cmd(token); //| LEMBRAR DE TRATAR '$0' E '$$'.
	else if (!strcmp(token[0], "export"))
		export_cmd(main, token);
	else if (!strcmp(token[0], "unset"))
		unset_cmd(main,token);
	else if (!strcmp(token[0], "cd"))
		cd_cmd(main, token);
	else if (!strcmp(token[0], "clear")) //| TIRAR FUTURAMENTE
		printf(CLEAR);
	free_matrix(token);
}
