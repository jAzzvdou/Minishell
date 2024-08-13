/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:07:15 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/13 17:07:53 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	calculate_total_length(char **matrix)
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

void	copy_string_to_new_str(char *new_str, char *str, int *len)
{
	int	j;

	j = 0;
	while (str[j])
	{
		new_str[*len] = str[j];
		j++;
		(*len)++;
	}
}
