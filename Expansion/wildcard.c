/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:30:59 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/20 17:14:16 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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
			add_token(expanded, wildcard->type,
				ft_strdup((char *)entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	if (!expanded->first)
		add_token(expanded, wildcard->type, ft_strdup(wildcard->cmd));
	return (expanded);
}

void	merge_list(t_tokens *source_list, t_tokens *target_list)
{
	t_node	*tmp;

	if (source_list)
	{
		tmp = source_list->first;
		while (tmp)
		{
			add_token(target_list, tmp->type, ft_strdup(tmp->cmd));
			tmp = tmp->next;
		}
		free_tokens2(source_list);
	}
}

t_tokens	*merge_lists(t_tokens *list1, t_tokens *list2)
{
	t_tokens	*new;

	if (!list1->first && !list2->first)
		return (NULL);
	new = start_tokens();
	merge_list(list1, new);
	merge_list(list2, new);
	return (new);
}

t_tokens	*handle_wildcard(t_tokens *tokens, t_node *tmp, t_tokens *expanded)
{
	t_tokens	*aux;

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

	tmp = tokens->first;
	expanded = NULL;
	while (tmp)
	{
		if (tmp->type == CMD && ft_strchr(tmp->cmd, '*'))
			expanded = handle_wildcard(tokens, tmp, expanded);
		tmp = tmp->next;
	}
	if (!expanded)
		return (tokens);
	free_tokens2(tokens);
	return (expanded);
}
