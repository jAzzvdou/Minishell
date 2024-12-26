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
	new->cmd = my_strdup(line);
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

void	build_tokens_loop(char **splited, t_tokens *tokens)
{
	int	ii;

	ii = 0;
	while (splited[ii])
	{
		if (!my_strcmp(splited[ii], "&&"))
			add_token(tokens, AND, splited[ii]);
		else if (!my_strcmp(splited[ii], "||"))
			add_token(tokens, OR, splited[ii]);
		else if (!my_strcmp(splited[ii], "|"))
			add_token(tokens, PIPE, splited[ii]);
		else if (!my_strcmp(splited[ii], ">"))
			add_token(tokens, OUTPUT, splited[ii]);
		else if (!my_strcmp(splited[ii], ">>"))
			add_token(tokens, APPEND, splited[ii]);
		else if (!my_strcmp(splited[ii], "<"))
			add_token(tokens, INPUT, splited[ii]);
		else if (!my_strcmp(splited[ii], "<<"))
			add_token(tokens, HEREDOC, splited[ii]);
		else if (splited[ii][0] == '(')
			add_token(tokens, BLOCK, splited[ii]);
		else if (my_strcmp(splited[ii], ""))
			add_token(tokens, CMD, splited[ii]);
		ii++;
	}
}

t_tokens	*build_tokens(char **split)
{
	int			i;
	char		**splited;
	t_tokens	*tokens;

	tokens = start_tokens();
	i = 0;
	while (split[i])
	{
		splited = spliter(split[i]);
		build_tokens_loop(splited, tokens);
		free(splited);
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
