/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:23:31 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/20 16:23:47 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	split_variables_1(char **cmd, int *i, char **split, int *j)
{
	char	*start;

	start = &(*cmd)[*i];
	while ((*cmd)[*i] && (*cmd)[*i] == ' ')
		(*i)++;
	split[(*j)++] = ft_strndup(start, *i - (start - *cmd));
}

// Função auxiliar para lidar com aspas
void	split_variables_2(char **cmd, int *i, char **split, int *j)
{
	char	quote;
	char	*start;

	start = &(*cmd)[*i];
	quote = (*cmd)[(*i)++];
	while ((*cmd)[*i] && (*cmd)[*i] != quote)
		(*i)++;
	if ((*cmd)[*i] == quote)
		(*i)++;
	split[(*j)++] = ft_strndup(start, *i - (start - *cmd));
}

// Função auxiliar para lidar com símbolos $
void	split_variables_3(char **cmd, int *i, char **split, int *j)
{
	char	*start;

	start = &(*cmd)[*i];
	(*i)++;
	while ((*cmd)[*i] && can_continue((*cmd)[*i]))
		(*i)++;
	split[(*j)++] = ft_strndup(start, *i - (start - *cmd));
}

// Função auxiliar para lidar com texto regular
void	split_variables_4(char **cmd, int *i, char **split, int *j)
{
	char	*start;

	start = &(*cmd)[*i];
	while ((*cmd)[*i] && can_continue((*cmd)[*i]))
		(*i)++;
	split[(*j)++] = ft_strndup(start, *i - (start - *cmd));
}
