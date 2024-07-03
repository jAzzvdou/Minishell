/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:38:33 by btaveira          #+#    #+#             */
/*   Updated: 2024/07/02 14:39:56 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_everything(t_main *main)
{
	free(main->pwd);
	main->pwd = NULL;
	free(main->old_pwd);
	main->old_pwd = NULL;
	free_env(&main->env);
	free_tokens(&main->tokens);
	free_tree(&main->tree);
	rl_clear_history();
}
