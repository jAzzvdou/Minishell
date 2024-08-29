/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:19 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/29 14:09:21 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*get_block(t_tokens *exec)
{
	t_node	*tmp;

	tmp = exec->first;
	while (tmp)
	{
		if (tmp->type == BLOCK)
			return (tmp->cmd);
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_reexec(t_main *main)
{
	if (main->pwd)
	{
		free(main->pwd);
		main->pwd = NULL;
	}
	if (main->old_pwd)
	{
		free(main->old_pwd);
		main->old_pwd = NULL;
	}
	free_env(&main->env);
	rl_clear_history();
}

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
		free_tree2(main->tree);
		parser(main, tokenizator(new_input));
		free_reexec(main);
		exit(last_status(-1));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	last_status(status);
}
