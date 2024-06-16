/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:42 by bruno             #+#    #+#             */
/*   Updated: 2024/06/16 20:26:18 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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

int     verify_parenthesis(char *input, int i)
{
        int     open;
        int     close;

        open = 0;
        close = 0;
        while (input[i])
        {
                if (input[i] == '(')
                        open++;
                else if (input[i] == ')')
                        close++;
                i++;
        }
        if (open == close)
                return (1);
        return (0);
}

int     skip_parenthesis(char *input, int i)
{
        int     open;
        int     close;

        open = 0;
        close = 0;
        while (input[i])
        {
                if (input[i] == '(')
                        open++;
                else if (input[i] == ')')
                        close++;
                i++;
                if (open == close)
                        break ;
        }
        return (i);
}
