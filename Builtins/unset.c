#include "../Include/minishell.h"

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->name);
		node->name = NULL;
		free(node->value);
		node->value = NULL;
		free(node->line);
		node->line = NULL;
		free(node);
		node = NULL;
	}
}

void	unset_cmd(t_main *main, char **token)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;

	i = 0;
	while (token[++i])
	{
		tmp = main->env;
		prev = NULL;
		while (tmp)
		{
			if (!my_strcmp(tmp->name, token[i]))
			{
				if (prev)
					prev->next = tmp->next;
				else
					main->env = tmp->next;
				free_env_node(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	last_status(0);
}
