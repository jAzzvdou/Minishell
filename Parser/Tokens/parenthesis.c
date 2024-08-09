/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:23:10 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 17:23:11 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	closed_parenthesis(char *s)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (*s)
	{
		if (*s == '(')
			left++;
		else if (*s == ')')
			right++;
		if (right > left)
			break ;
		if (!skip_quotes(&s))
			s++;
	}
	if (right == left)
		return (1);
	return (0);
}

int	verify_parenthesis(char *input, int i)
{
	int	open;
	int	close;

	open = 0;
	close = 0;
	while (input[i])
	{
		if (input[i] == '(')
			open++;
		else if (input[i] == ')')
			close++;
		if ((input[i] == '\'' || input[i] == '\"')
			&& verify_quote(input, i))
			i += is_quote(input, i) - i;
		i++;
	}
	if (open == close)
		return (1);
	return (debug(), 0);
}

int	skip_parenthesis(char *input, int i)
{
	int	open;
	int	close;

	open = 0;
	close = 0;
	while (input[i])
	{
		if (input[i] == '(')
			open++;
		else if (input[i] == ')')
			close++;
		if ((input[i] == '\'' || input[i] == '\"')
			&& verify_quote(input, i))
			i += is_quote(input, i);
		i++;
		if (open == close)
			break ;
	}
	return (i);
}
