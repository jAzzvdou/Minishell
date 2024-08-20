/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:13:08 by btaveira          #+#    #+#             */
/*   Updated: 2024/08/20 17:14:20 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_tokens	*before_wildcard(t_tokens *tokens, t_node *node)
{
	t_node		*tmp;
	t_tokens	*before;

	before = start_tokens();
	tmp = tokens->first;
	while (tmp && ft_strcmp(tmp->cmd, node->cmd))
	{
		add_token(before, tmp->type, ft_strdup(tmp->cmd));
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
	while (tmp && ft_strcmp(tmp->cmd, node->cmd))
		tmp = tmp->next;
	while (tmp)
	{
		add_token(after, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	return (after);
}

int	process_pattern(const char **f, const char **p,
	const char **star, const char **match)
{
	if (**p == '*')
	{
		*star = *p;
		(*p)++;
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
		return (1);
	return (0);
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
	while (*f)
	{
		if (process_pattern(&f, &p, &star, &match))
			return (0);
	}
	while (*p == '*')
		p++;
	if (*p)
		return (0);
	return (1);
}
