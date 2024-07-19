#include "../Include/minishell.h"

t_tokens	*before_wildcard(t_tokens *tokens, t_tokens *wildcard)
{
	t_tokens	*tmp;
	t_tokens	*before;

	before = start_tokens();
	tmp = tokens;
	while (tmp)
	{
		if (tmp == wildcard)
			break ;
		add_token(before, tmp->type, tmp->cmd);
		tmp = tmp->next;
	}
	free_tokens(tokens);
	return (before);
}

t_tokens	*after_wildcard(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*after;

	after = start_tokens(); 
	tmp = tokens;
	while (tmp)
	{
		add_token(after, tmp->type, tmp->cmd);
		tmp = tmp->next;
	}
	return (after);
}

t_tokens	*expand_wildcard(t_tokens *wildcard)
{
	DIR	*dir;
	struct dirent	*entry;
	t_tokens	*expanded;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	while (/*Enquanto tiver coisa na pasta*/)
	{
		if (/*Se for direfente de '.' e se encaixar no pattern*/)
			//Entre na lista;
	}
	closedir();
	return (expanded);
}

t_tokens	*merge_lists(t_tokens *list1, t_tokens *list2)
{
	//| JUNTAR AS DUAS LISTAS.
}

t_tokens	*wildcard(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*after;
	t_tokens	*expanded;

	after = NULL;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->first->type == CMD
			&& ft_strchr(tmp->first->cmd, '*'))
		{
			if (tmp->next)
				after = after_wildcard(tmp->next);
			if (tmp->prev)
				before = before_wildcard(tokens, tmp);
			expanded = expand_wildcard(tmp);
			expanded = merge_lists(before, expanded);
			expanded = merge_lists(expanded, after);
		}
		tmp = tmp->next;
	}
	return (expanded);
}

t_tokens	*expander(t_tokens *tokens)
{
	t_tokens	*expanded;
	t_tokens	*tmp;

	tmp = wildcard(tokens); //| Expandir *.
	expanded = expansion_var(tmp); //| Expandir VAR.
	free(tmp);
	tmp = NULL;
	return (expanded);
}
/*
t_token *expand_wildcard(const char *pattern) {
    DIR *dir;
    struct dirent *entry;
    t_token *expanded_tokens = NULL;

    dir = opendir(".");
    if (!dir)
        return NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (*(char *)entry->d_name != '.' && fnmatch(pattern, entry->d_name, 0) == 0) {
            t_token *new_token = create_token(entry->d_name);
            if (new_token)
                add_token(&expanded_tokens, new_token);
        }
    }

    closedir(dir);
    return expanded_tokens;
}
*/
