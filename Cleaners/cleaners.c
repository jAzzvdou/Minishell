#include "../Include/minishell.h"

void	free_var(char *name)
{
	free(name);
	name = NULL;
}

void	free_env(t_env **env)
{
	t_env	*aux;

	if (!*env)
		return ;
	while (*env)
	{
		aux = *env;
		*env = (*env)->next;
		if (aux->name)
			free_var(aux->name);
		if (aux->value)
			free_var(aux->value);
		if (aux->line)
			free_var(aux->line);
		free(aux);
		aux = NULL;
	}
	*env = NULL;
}

void	free_tokens2(t_tokens *tokens)
{
	t_node	*current_node;
	t_node	*next_node;

	if (!tokens)
		return ;
	current_node = tokens->first;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->cmd)
		{
			free(current_node->cmd);
			current_node->cmd = NULL;
		}
		free(current_node);
		current_node = NULL;
		current_node = next_node;
	}
	free(tokens);
	tokens = NULL;
}

void	free_tree2(t_tree *tree)
{
	t_node	*current;
	t_node	*next;

	if (!tree)
		return ;
	free_tree2(tree->left);
	free_tree2(tree->right);
	if (tree->exe)
	{
		current = tree->exe->first;
		while (current)
		{
			next = current->next;
			if (current->cmd)
				free(current->cmd);
			free(current);
			current = next;
		}
		free(tree->exe);
	}
	free(tree);
}

void	free_tree(t_tree **tree)
{
	if (!*tree)
		return ;
	free_tree(&(*tree)->left);
	free_tree(&(*tree)->right);
	free(*tree);
	*tree = NULL;
}
