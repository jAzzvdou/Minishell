/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:45:23 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/14 10:55:41 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_type	get_token_type(char *str)
{
	if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else if (!ft_strcmp(str, "<"))
		return (INPUT);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else if (str[0] == '(')
		return (BLOCK);
	return (CMD);
}

void	process_individual_token(t_tokens *tokens, char *token_str)
{
	t_type	type;

	if (ft_strcmp(token_str, "") != 0)
	{
		type = get_token_type(token_str);
		add_token(tokens, type, token_str);
	}
}

void	process_split_string(t_tokens *tokens, char **splited)
{
	int	ii;

	ii = 0;
	while (splited[ii])
	{
		process_individual_token(tokens, splited[ii]);
		ii++;
	}
	free(splited);
}
