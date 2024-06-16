#include "minishell.h"

void    free_matrix(char ***matrix)
{
        int     i;

        //| Caso não tenha matrix, só retorna.
        if (!*matrix)
                return ;
        i = -1;
        while ((*matrix)[++i])
        {
                free((*matrix)[i]); //| Free direto no endereço.
                (*matrix)[i] = NULL;//| Setando para NULL para não ter double free.
        }
        free(*matrix); //| Libera a matrix.
        *matrix = NULL;
}
