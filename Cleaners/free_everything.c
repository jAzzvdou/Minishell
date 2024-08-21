/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:20 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/21 15:58:29 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_everything(t_main *main)
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
	free_tree2(main->tree);
	rl_clear_history();
}
