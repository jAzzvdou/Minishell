/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:15:51 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/19 17:19:31 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

typedef struct s_cmd
{
	char	*command; //| MALLOCADO
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_history
{
	t_cmd	*first;   //| MALLOCADO
	t_cmd	*last;    //| MALLOCADO
	t_cmd	*current; //| MALLOCADO
}	t_history;

char	*my_readline(char *prompt)
{
	char	*line;

	printf("%s", prompt);
	line = get_next_line(STDIN_FILENO);
	return (line);
}

t_history	*start_history(void)
{
	t_history	*history;

	history = (t_history *)malloc(sizeof(t_history));
	history->first = NULL;
	history->last = NULL;
	history->current = NULL;
	return (history);
}

//| Para usar essa função a gente tem que inicializar ela antes do while true.
void	my_add_history(t_history *history, char *user_input)
{
	t_cmd	*new;

	new = (t_new *)malloc(sizeof(t_new));
	new->command = ft_strdup(user_input);
	next->prev = history->last;
	new->next = NULL;
	if (new->last)
		history->last->next = new;
	else
		history->first = new;
	history->last = new;
	history->current = NULL;
}

// Pegar o comando anterior (se existir)
char	*get_prev_cmd(t_history *history)
{
	if (!history->current)
		history->current = history->last;
	else if (history->current->prev)
		history->current = history->current->prev;
	if (history->current)
		return (history->current->command);
	return (NULL);
}

// Pegar o comando posterior (se existir)
char	*get_next_cmd(t_history *history)
{
	if (history->current && history->current->next)
		history->current = history->current->next;
	else
		history->current = NULL;
	if (history->current)
		return (history->current->command);
	return (NULL);
}

//| FALTA FAZER O 'ENABLE_RAW_MODE()' E O 'DISABLE_RAW_MODE()'.
