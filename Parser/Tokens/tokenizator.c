/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:23:46 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/14 10:58:08 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_tokens	*start_tokens(void)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	tokens->size = 0;
	tokens->first = NULL;
	tokens->last = NULL;
	return (tokens);
}

void	add_token(t_tokens *tokens, t_type type, char *line)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->type = type;
	new->cmd = ft_strdup(line);
	free(line);
	new->next = NULL;
	new->prev = tokens->last;
	if (tokens->last)
		tokens->last->next = new;
	else
		tokens->first = new;
	tokens->last = new;
	tokens->size++;
}

t_tokens	*build_tokens(char **split)
{
	int			i;
	char		**splited;
	t_tokens	*tokens;

	i = 0;
	tokens = start_tokens();
	while (split[i])
	{
		splited = spliter(split[i]);
		process_split_string(tokens, splited);
		i++;
	}
	free_matrix(split);
	return (tokens);
}

t_tokens	*tokenizator(char *user_input)
{
	char		**split;
	t_tokens	*tokens;

	skip_spaces(&user_input);
	if (!*user_input)
		return (NULL);
	if (!closed_quotes(user_input) || !closed_parenthesis(user_input))
		return (error_closed());
	split = split_input(user_input);
	free(user_input);
	if (!split)
	{
		err(RED"Error!\n"RESET);
		return (NULL);
	}
	tokens = build_tokens(split);
	return (tokens);
}
