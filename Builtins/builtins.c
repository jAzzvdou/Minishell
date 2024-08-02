/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:45 by bruno             #+#    #+#             */
/*   Updated: 2024/08/02 10:23:34 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_args(char **args, int i)
{
	while (i > 0)
	{
		free(args[--i]);
		args[i] = NULL;
	}
	free(args);
	args = NULL;
}

char	**token_to_args(t_tokens *tokens)
{
	int		i;
	int		ii;
	char	**args;
	t_node	*node;

	if (!tokens || !tokens->first || !tokens->size)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (tokens->size + 1));
	node = tokens->first;
	i = 0;
	ii = -1;
	while (++ii < tokens->size)
	{
		args[i] = ft_strdup(node->cmd);
		if (!args[i])
			return (free_args(args, i), NULL);
		i++;
		node = node->next;
	}
	args[i] = NULL;
	return (args);
}

int	last_status(int new_status)
{
	static int	status;

	if (new_status > -1)
		status = new_status;
	return (status);
}

int	builtins(t_main *main, char **token)
{
	if (!token || !token[0])
		return (0);
	if (!ft_strcmp(token[0], "exit"))
		return (exit_cmd(main, token), 1);
	else if (!ft_strcmp(token[0], "env"))
		return (env_cmd(main, token), 1);
	else if (!ft_strcmp(token[0], "pwd"))
		return (printf("%s\n", main->pwd), 1);
	else if (!ft_strcmp(token[0], "echo"))
		return (echo_cmd(token), 1);
	else if (!ft_strcmp(token[0], "export"))
		return (export_cmd(main, token), 1);
	else if (!ft_strcmp(token[0], "unset"))
		return (unset_cmd(main, token), 1);
	else if (!ft_strcmp(token[0], "cd"))
		return (cd_cmd(main, token), 1);
	return (0);
}
