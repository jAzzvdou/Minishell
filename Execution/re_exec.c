/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:40:55 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/02 12:28:37 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	re_exec(t_main *main, char *block)
{
	int		status;
	char	*new_input;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		new_input = ft_strndup(block + 1, ft_strlen(block) - 2);
		free(block);
		block = NULL;
		parser(main, tokenizator(new_input));
		free_everything(main);
		exit(last_status(-1));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	last_status(status);
}
