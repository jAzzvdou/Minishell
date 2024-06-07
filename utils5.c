#include "minishell.h"

void    skip_spaces(const char **s)
{
        while (**s && is_space(**s))
                (*s)++;
}

static int      skip_quotes(const char **s)
{
        char    quote;

        if (**s == '\'' || **s == '"')
                quote = **s;
        else
                return (0);
        (*s)++;
        while (**s && **s != quote)
                (*s)++;
        if (**s)
                (*s)++;
        return (1);
}

int     closed_parenthesis(const char *s)
{
        int     left;
        int     right;

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

int     closed_quotes(const char *s)
{
        char    quote;

        while (*s)
        {
                if (*s == '\'' || *s == '"')
                {
                        quote = *s;
                        s++;
                        while (*s && *s != quote)
                                s++;
                        if (!*s)
                                return (0);
                }
                s++;
        }
        return (1);
}
