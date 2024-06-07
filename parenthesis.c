#include "minishell.h"

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
