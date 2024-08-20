/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:28:02 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/20 15:30:26 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	skip_spaces_split_variable(char *cmd, int i)
{
	while (cmd[i] && cmd[i] == ' ')
		i++;
	return (i);
}

int	handle_quote_segment(char *cmd, int i, int *words)
{
	char	quote;

	(*words)++;
	quote = cmd[i++];
	while (cmd[i] && cmd[i] != quote)
		i++;
	if (cmd[i] == quote)
		i++;
	return (i);
}

int	handle_dollar_segment(char *cmd, int i, int *words)
{
	(*words)++;
	i++;
	while (cmd[i] && can_continue(cmd[i]))
		i++;
	return (i);
}

int	handle_regular_segment(char *cmd, int i, int *words)
{
	(*words)++;
	while (cmd[i] && can_continue(cmd[i]))
		i++;
	return (i);
}
