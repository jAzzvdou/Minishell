#include "../Include/minishell.h"

void	free_exit(t_main *main, char **env, char **tokens, char *cmd)
{
	err(GREY"minichad: ");
	err(cmd);
	err(": command not found\n"WHITE);
	free_matrix(env);
	free_matrix(tokens);
	free_everything(main);
	exit(127);
}

void	free_nodes(t_node *node)
{
	t_node	*aux;

	if (!node)
		return ;
	while (node)
	{
		aux = node;
		node = node->next;
		if (aux->cmd)
		{
			free(aux->cmd);
			aux->cmd = NULL;
		}
		free(aux);
		aux = NULL;
	}
}

void	free_tokens(t_tokens **tokens)
{
	if (!*tokens)
		return ;
	free_nodes((*tokens)->first);
	(*tokens)->first = NULL;
	(*tokens)->last = NULL;
	free(*tokens);
	*tokens = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}
