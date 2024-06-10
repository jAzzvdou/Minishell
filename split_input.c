#include "minishell.h"

static void     free_split(char **final)
{
        int     i;

        i = -1;
        while (final[++i])
                free(final[i]);
        free(final);
}

/*
int	is_operator(char *input, int i)
{
	if (!ft_strncmp(input + i, "&&", 2)
		|| !ft_strncmp(input + i, "||", 2)
		|| input[i] == '|')
		return (1);
	return (0);
}
int	witch_operator(char *input, int i)
{
	if (!ft_strncmp(input + i, "&&", 2)
		|| !ft_strncmp(input + i, "||", 2))
		return (2);
	return (1);
}
*/

static int      count_words(char *input)
{
        int     i;
        int     words;

        i = 0;
        words = 0;
        while (input[i])
        {
                if (input[i] != ' ')
                        words++;
                if ((input[i] == '\'' || input[i] == '\"') && verify_quote(input, i))
                        i += is_quote(input, i);
		else if ((input[i] == '(' && verify_parenthesis(input, i)))
			i += skip_parenthesis(input, i);
                while (input[i] && input[i] != ' ')
                        input++;
                while (input[i] && input[i] == ' ')
                        input++;
        }
        return (words);
}

static char     **final_split(char **final, char *input, int words)
{
        int     i;
        int     counter;

        counter = -1;
        while (++counter < words)
        {
		while (*input == ' ')
			input++;
                i = 0;
                if ((input[i] == '\'' || input[i] == '\"') && verify_quote(input, i))
                        i += is_quote(input, i);
		else if ((input[i] == '(' && verify_parenthesis(input, i)))
			i += skip_parenthesis(input, i);
                while (input[i] && input[i] != ' ')
                        i++;
                final[counter] = ft_substr(input, 0, i);
                if (!final[counter])
                        return (free_split(final), NULL);
                input += i;
        }
        return (final[counter] = NULL, final);
}

char    **split_input(char *input)
{
        int             i;
        int             words;
        char    **final;
        char    **trim;

        if (!input)
                return (NULL);
        words = count_words(input);
        final = (char **)malloc(sizeof(char *) * (words + 1));
        if (!final)
                return (NULL);
        trim = final_split(final, input, words);
        i = -1;
        while (trim[++i])
        {
                if ((trim[i][0] == '\'' || trim[i][0] == '\"')
                        && verify_quote(trim[i], 0))
                        trim[i] = remove_quote(trim[i], trim[i][0]);
		else if ((trim[i][0] == '(' && verify_parenthesis(trim[i], 0)))
			trim[i] = ft_strtrim(trim[i], "()");
        }
        return (trim);
}
