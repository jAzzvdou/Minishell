/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:35:45 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/29 14:36:19 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	get_matrix_len(char **matrix)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (matrix[i])
	{
		len += ft_strlen(matrix[i]);
		i++;
	}
	return (len);
}

char	*concatenator(char **matrix)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	len = get_matrix_len(matrix);
	new_str = malloc(sizeof(char) * len + 1);
	i = 0;
	len = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			new_str[len] = matrix[i][j];
			j++;
			len++;
		}
		i++;
	}
	new_str[len] = '\0';
	free_matrix(matrix);
	return (new_str);
}
