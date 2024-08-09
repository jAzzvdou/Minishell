/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:20:53 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 17:20:55 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	start_pwd(t_main *main)
{
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	main->pwd = ft_strdup(cwd);
	main->old_pwd = ft_strdup(cwd);
}
