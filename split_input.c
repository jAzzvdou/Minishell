#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	is_operator(const char *input, int index)
{
    return (input[index] == '|' && input[index + 1] == '|') || 
           (input[index] == '&' && input[index + 1] == '&') || 
           input[index] == '|';
}

int	count_tokens(char *input)
{
	int count = 0;
	int i = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i])) i++; // Skip spaces
		if (input[i] == '\0') break;
		if (is_operator(input, i))
		{
			count++;
			if (input[i] == '|' && input[i + 1] == '|') i += 2;
			else if (input[i] == '&' && input[i + 1] == '&') i += 2;
			else i++;
		}
		else
		{
			count++;
			while (input[i] && !is_operator(input, i)) i++;
		}
	}
	return count;
}

char	**split_input(char *input)
{
	int token_count = count_tokens(input);
	char **result = malloc((token_count + 1) * sizeof(char *));
	int i = 0, k = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i])) i++;
		if (input[i] == '\0') break;
		int start = i;
		if (is_operator(input, i))
		{
			int len = (input[i] == '|' && input[i + 1] == '|') || (input[i] == '&' && input[i + 1] == '&') ? 2 : 1;
			result[k] = malloc((len + 1) * sizeof(char));
			strncpy(result[k], input + i, len);
			result[k][len] = '\0';
			i += len;
		}
		else
		{
			while (input[i] && !is_operator(input, i)) i++;
			while (i > start && is_space(input[start])) start++;
			while (i > start && is_space(input[i - 1])) i--;
			result[k] = malloc((i - start + 1) * sizeof(char));
			strncpy(result[k], input + start, i - start);
			result[k][i - start] = '\0';
		}
		k++;
	}
	result[k] = NULL;
	return result;
}
