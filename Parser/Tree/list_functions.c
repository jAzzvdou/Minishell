/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:24:10 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/19 17:26:56 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_tokens	*get_right(t_tokens *tokens, t_node *node)
{
	t_node		*tmp;
	t_tokens	*right;

	if (!tokens || !node)
		return (NULL);
	right = start_tokens();
	tmp = tokens->first;
	while (tmp && tmp != node)
		tmp = tmp->next;
	while (tmp)
	{
		add_token(right, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	return (right);
}

t_tokens	*get_left(t_tokens *tokens, t_node *node)
{
	t_node		*tmp;
	t_tokens	*left;

	if (!tokens || !node)
		return (NULL);
	left = start_tokens();
	tmp = tokens->first;
	while (tmp && tmp != node)
	{
		add_token(left, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	free_tokens2(tokens);
	return (left);
}

t_tokens	*remove_last(t_tokens *right)
{
	t_node		*tmp;
	t_tokens	*new_right;

	if (!right)
		return (NULL);
	new_right = start_tokens();
	tmp = right->first->next;
	while (tmp)
	{
		add_token(new_right, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	free_tokens2(right);
	return (new_right);
}

t_tokens	*get_from_right(t_tokens *left, t_tokens *right)
{
	t_node		*tmp;
	t_tokens	*new_left;

	if (!left || !right)
		return (NULL);
	new_left = start_tokens();
	tmp = left->first;
	while (tmp)
	{
		add_token(new_left, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	tmp = right->first->next;
	while (tmp)
	{
		add_token(new_left, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	free_tokens2(left);
	return (new_left);
}

t_tokens	*send_to_left(t_tokens *right)
{
	t_node		*tmp;
	t_tokens	*new_right;

	if (!right)
		return (NULL);
	new_right = start_tokens();
	tmp = right->first;
	add_token(new_right, tmp->type, ft_strdup(tmp->cmd));
	free_tokens2(right);
	return (new_right);
}
