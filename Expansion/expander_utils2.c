/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:43:21 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/20 14:56:08 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	expand_loop(char **splited, char *tmp, t_main *main)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\'')
		{
			tmp = splited[i];
			splited[i] = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
			free(tmp);
		}
		else
		{
			tmp = splited[i];
			splited[i] = change_var(main, tmp);
			free(tmp);
		}
		if (!splited[i])
			splited[i] = ft_strdup("\0");
		i++;
	}
}

char	*expand(t_main *main, char *cmd)
{
	char	*tmp;
	char	**splited;

	tmp = NULL;
	splited = split_variable(cmd);
	expand_loop(splited, tmp, main);
	tmp = concatenator(splited);
	return (tmp);
}

char	*not_expand(char *cmd)
{
	int		i;
	char	*tmp;
	char	**splited;

	splited = split_variable(cmd);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\"' || splited[i][0] == '\'')
		{
			tmp = splited[i];
			splited[i] = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
			free(tmp);
		}
		if (!splited[i])
			splited[i] = ft_strdup("\0");
		i++;
	}
	tmp = concatenator(splited);
	return (tmp);
}

int	is_valid(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c == '0') || (c == '?') || (c == '-') || (c == '_'))
		return (1);
	return (0);
}
