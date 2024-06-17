/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:11:02 by bruno             #+#    #+#             */
/*   Updated: 2024/06/16 22:28:52 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

void	start_pwd(t_main *main)
{
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	main->pwd = ft_strdup(cwd);
	main->old_pwd = ft_strdup(cwd);
}
