#include "minishell.h"

t_tokens	*start_tokens(void)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	tokens->size = 0;
	tokens->first = NULL;
	tokens->last = NULL;
	return (tokens);
}

void	add_token(t_tokens *tokens, e_type type, char *line)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->type = type;
	new->cmd = line;
	new->cmd_args = spliter(line);
	new->next = NULL;
	new->prev = tokens->last;
	if (tokens->last)
		tokens->last->next = new;
	else
		tokens->first = new;
	tokens->last = new;
	tokens->size++;
}

t_tokens	*tokenizator(char *user_input)
{
	int		i;
	char		**splited;
	t_tokens	*tokens;

	skip_spaces(&user_input);
	if (!*user_input)
		return (NULL);
	if (!closed_quotes(user_input) || !closed_parenthesis(user_input))
	{
		printf(RED"Error!\n");
		printf(GREY"\tMinishell Only Parses Closed Quotes/Parenthesis.\n");
		return (NULL);
	}
	tokens = start_tokens();
	//| MUDAR A SPLITER
	splited = spliter(user_input);
	i = -1;
	while (splited[++i])
	{
		if (!strcmp(splited[i], "&&"))
			add_token(tokens, AND, splited[i]);
		else if (!strcmp(splited[i], "||"))
			add_token(tokens, OR, splited[i]);
		else if (!strcmp(splited[i], "|"))
			add_token(tokens, PIPE, splited[i]);
		else if (!strcmp(splited[i], ">"))
			add_token(tokens, OUTPUT, splited[i]);
		else if (!strcmp(splited[i], ">>"))
			add_token(tokens, APPEND, splited[i]);
		else if (!strcmp(splited[i], "<"))
			add_token(tokens, INPUT, splited[i]);
		else if (!strcmp(splited[i], "<<"))
			add_token(tokens, HEREDOC, splited[i]);
		else
			add_token(tokens, CMD, splited[i]);
	}
	free_matrix(&splited);
	return (tokens);
}
