#include "../Include/minishell.h"

int	get_matrix_len(char **matrix)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (matrix[i])
	{
		len += my_strlen(matrix[i]);
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
