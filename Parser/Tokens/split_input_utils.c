/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:14:26 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/14 13:34:01 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	skip_spaces2(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

int	skip_separator(char *input, int i)
{
	if (!strncmp(input + i, ">>", 2) || !strncmp(input + i, "<<", 2) \
		|| !strncmp(input + i, "&&", 2) || !strncmp(input + i, "||", 2))
		return (i + 2);
	return (i + 1);
}

int	process_non_separator(char *input, int i)
{
	while (input[i] && !is_separator(input, i))
	{
		if ((input[i] == '\'' || input[i] == '\"') && verify_quote(input, i))
			i = is_quote(input, i);
		else if (input[i] == '(' && verify_parenthesis(input, i))
			i = skip_parenthesis(input, i);
		else
			i++;
	}
	return (i);
}
