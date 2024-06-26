/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:45 by bruno             #+#    #+#             */
/*   Updated: 2024/06/26 16:32:07 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

/*
void	expander(t_tokens *tokens)
{
	asterisk(tokens);
	//| passar todos os tokens pela função que vai expandir os $.
}
*/

char    **token_to_args(t_tokens *tokens)
{
        int	i;
        char	**args;
        t_node	*node;

	if (!tokens)
	{
		err(RED"NULL.\n"RESET);
		return (NULL);
	}
	//| Aqui tem que fazer a função de expandir. -> t_tokens *expander(t_tokens *tokens);
	//| Dentro do expander a gente tem que dar free na lista.
	//| expander(tokens);
        node = tokens->first;
        i = 0;
        while (node)
        {
                i++;
                node = node->next;
        }
        args = (char **)malloc(sizeof(char *) * (i + 1));
        i = 0;
        node = tokens->first;
        while (node)
        {
                args[i] = ft_strdup(node->cmd);
                i++;
                node = node->next;
        }
        args[i] = NULL;
        return (args);
}

int	builtins(t_main *main, char **token)
{
	if (!token)
		return (0);
	if (!strcmp(token[0], "exit"))
		return (exit_cmd(main, token), 1);
	else if (!strcmp(token[0], "env"))
		return (env_cmd(main, token), 1);
	else if (!strcmp(token[0], "pwd"))
		return (printf("%s\n", main->pwd), 1);
	else if (!strcmp(token[0], "echo"))
		return (echo_cmd(token), 1); //| LEMBRAR DE TRATAR '$0' E '$$'.
	else if (!strcmp(token[0], "export"))
		return (export_cmd(main, token), 1);
	else if (!strcmp(token[0], "unset"))
		return (unset_cmd(main,token), 1);
	else if (!strcmp(token[0], "cd"))
		return (cd_cmd(main, token), 1);
	else if (!strcmp(token[0], "clear")) //| TIRAR FUTURAMENTE
		return (printf(CLEAR), 1);
	free_matrix(token);
	return (0);
}
