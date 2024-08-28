/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:30:59 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/28 14:01:24 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_tokens	*expand_wildcard(t_node *wildcard)
{
	char			*tmp;
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
		{
			tmp = ft_strdup((char *)entry->d_name);
			add_token(expanded, wildcard->type, tmp);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (!expanded->first)
		add_token(expanded, wildcard->type, ft_strdup(wildcard->cmd));
	return (expanded);
}

t_tokens	*merge_lists(t_tokens *list1, t_tokens *list2)
{
	t_node		*tmp;
	t_tokens	*new;

	new = start_tokens();
	if (list1)
	{
		tmp = list1->first;
		while (tmp)
		{
			add_token(new, tmp->type, ft_strdup(tmp->cmd));
			tmp = tmp->next;
		}
		free_tokens2(list1);
	}
	if (list2)
	{
		tmp = list2->first;
		while (tmp)
		{
			add_token(new, tmp->type, ft_strdup(tmp->cmd));
			tmp = tmp->next;
		}
		free_tokens2(list2);
	}
	return (new);
}

t_tokens	*expand_and_merge_wildcard(t_tokens *tokens, t_node *tmp)
{
	t_tokens	*aux;
	t_tokens	*expanded;

	expanded = expand_wildcard(tmp);
	if (tmp->prev)
	{
		aux = before_wildcard(tokens, tmp);
		expanded = merge_lists(aux, expanded);
	}
	if (tmp->next)
	{
		aux = after_wildcard(tokens, tmp->next);
		expanded = merge_lists(expanded, aux);
	}
	return (expanded);
}

t_tokens	*wildcard(t_tokens *tokens)
{
	t_node		*tmp;
	t_tokens	*expanded;

	expanded = NULL;
	tmp = tokens->first;
	while (tmp)
	{
		if (tmp->type == CMD && ft_strchr(tmp->cmd, '*'))
		{
			expanded = expand_and_merge_wildcard(tokens, tmp);
		}
		tmp = tmp->next;
	}
	if (!expanded)
		return (tokens);
	free_tokens2(tokens);
	return (expanded);
}
