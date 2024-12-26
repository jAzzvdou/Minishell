#include "../Include/minishell.h"

void	err_equal_sign(char *token)
{
	err(GREY"minichad: export: '");
	err(token);
	err("': need '=' after variable name\n"RESET);
	last_status(1);
}

void	swap_nodes(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->line;
	a->line = b->line;
	b->line = tmp;
}

t_env	*alphabetical_env(t_env *tmp)
{
	int			swapped;
	t_env		*ordered;
	t_env		*current;

	if (!tmp)
		return (NULL);
	ordered = tmp;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = ordered;
		while (current->next)
		{
			if (my_strcmp(current->line, current->next->line) > 0)
			{
				swap_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (ordered);
}

void	export_cmd(t_main *main, char **token)
{
	int	i;

	if (!token[1])
	{
		handle_no_args(main->env);
		return ;
	}
	i = 1;
	while (token[i])
	{
		if (!is_valid_identifier(token[i]))
		{
			err(GREY"minichad: export: '");
			err(token[i]);
			err("': not a valid identifier\n"RESET);
			last_status(1);
			i++;
			continue ;
		}
		handle_equal_sign(main, token[i]);
		i++;
	}
}
