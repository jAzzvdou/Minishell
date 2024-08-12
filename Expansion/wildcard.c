/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:30:59 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/12 17:58:33 by jazevedo         ###   ########.fr       */
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
		add_token(before, tmp->type, tmp->cmd);
		tmp = tmp->next;
	}
	//| free()?
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
		add_token(after, tmp->type, tmp->cmd);
		tmp = tmp->next;
	}
	//| free()?
	return (after);
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
		if (*p == '*')
		{
			star = p++;
			match = f;
		}
		else if (*p == *f)
		{
			p++;
			f++;
		}
		else if (star)
		{
			p = star + 1;
			match++;
			f = match;
		}
		else
			return (0);
	}
	while (*p == '*')
		p++;
	if (*p)
		return (0);
	return (1);
}

t_tokens	*expand_wildcard(t_node *wildcard)
{
	DIR				*dir;
	struct dirent	*entry;
	t_tokens		*expanded;

	expanded = start_tokens();
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (*(char *)entry->d_name != '.'
			&& is_match((char *)entry->d_name, wildcard->cmd))
			add_token(expanded, wildcard->type, (char *)entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	if (!expanded->first)
		add_token(expanded, wildcard->type, wildcard->cmd);
	return (expanded);
}

t_tokens	*merge_lists(t_tokens *list1, t_tokens *list2)
{
	t_node		*tmp;
	t_tokens	*new;

	if (!list1->first && !list2->first)
		return (NULL);
	new = start_tokens();
	if (list1)
	{
		tmp = list1->first;
		while (tmp)
		{
			add_token(new, tmp->type, tmp->cmd);
			tmp = tmp->next;
		}
		free_tokens2(list1);
	}
	if (list2)
	{
		tmp = list2->first;
		while (tmp)
		{
			add_token(new, tmp->type, tmp->cmd);
			tmp = tmp->next;
		}
		free_tokens2(list2);
	}
	return (new);
}

t_tokens	*wildcard(t_tokens *tokens)
{
	t_node		*tmp;
	t_tokens	*after;
	t_tokens	*before;
	t_tokens	*expanded;

	after = NULL;
	before = NULL;
	expanded = NULL;
	tmp = tokens->first;
	while (tmp)
	{
		if (tmp->type == CMD
			&& ft_strchr(tmp->cmd, '*'))
		{
			if (tmp->next)
				after = after_wildcard(tokens, tmp->next);
			if (tmp->prev)
				before = before_wildcard(tokens, tmp);
			expanded = expand_wildcard(tmp);
			expanded = merge_lists(before, expanded);
			expanded = merge_lists(expanded, after);
		}
		tmp = tmp->next;
	}
	if (!expanded)
		return (tokens);
	free_tokens2(tokens);
	return (expanded);
}
