#include "../Include/minishell.h"

t_tokens	*before_wildcard(t_tokens *tokens, t_node *node)
{
	t_node		*tmp;
	t_tokens	*before;

	before = start_tokens();
	tmp = tokens->first;
	while (tmp && my_strcmp(tmp->cmd, node->cmd))
	{
		add_token(before, tmp->type, my_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	return (before);
}

t_tokens	*after_wildcard(t_tokens *tokens, t_node *node)
{
	t_node		*tmp;
	t_tokens	*after;

	after = start_tokens();
	tmp = tokens->first;
	while (tmp && my_strcmp(tmp->cmd, node->cmd))
		tmp = tmp->next;
	while (tmp)
	{
		add_token(after, tmp->type, my_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	return (after);
}

int	match_loop(const char **f, const char **p, const char **star,
	const char **match)
{
	while (**f)
	{
		if (**p == '*')
		{
			*star = (*p)++;
			*match = *f;
		}
		else if (**p == **f)
		{
			(*p)++;
			(*f)++;
		}
		else if (*star)
		{
			*p = *star + 1;
			(*match)++;
			*f = *match;
		}
		else
			return (0);
	}
	return (1);
}

int	is_match(const char *file, const char *pattern)
{
	const char	*f;
	const char	*p;
	const char	*star;
	const char	*match;

	f = file;
	p = pattern;
	star = NULL;
	match = f;
	if (!match_loop(&f, &p, &star, &match))
		return (0);
	while (*p == '*')
		p++;
	if (*p)
		return (0);
	return (1);
}
