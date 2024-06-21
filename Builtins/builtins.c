/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:45 by bruno             #+#    #+#             */
/*   Updated: 2024/06/21 13:48:34 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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
