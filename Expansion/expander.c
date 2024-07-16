#include "../Include/minishell.h"

//| AQUI VAMOS EXPANDIR O WILDCARD E AS VARIÁVEIS DE AMBIENTE.

t_tokens	*wildcard(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->first->type == CMD
			&& ft_strchr(tmp->first->cmd, '*'))
		{
			//| Pegar a lista depois de *.
			//| tokens -> tokens expandidos.
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

/* Exemplo de Wildcard do Chat:
typedef struct s_token {
    char *str;
    struct s_token *next;
} t_token;

t_token *create_token(char *str) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->str = strdup(str);
    new_token->next = NULL;
    return new_token;
}

void add_token(t_token **tokens, t_token *new_token) {
    if (!*tokens) {
        *tokens = new_token;
        return;
    }
    t_token *temp = *tokens;
    while (temp->next)
        temp = temp->next;
    temp->next = new_token;
}

void free_tokens(t_token *tokens) {
    t_token *temp;
    while (tokens) {
        temp = tokens;
        tokens = tokens->next;
        free(temp->str);
        free(temp);
    }
}

t_token *split_tokens(t_token **tokens, t_token *wildcard) {
    t_token *after_wildcard = NULL;

    if (!wildcard || !tokens)
        return NULL;

    while (*tokens && *tokens != wildcard) {
        tokens = &(*tokens)->next;
    }

    if (*tokens) {
        after_wildcard = (*tokens)->next;
        (*tokens)->next = NULL;
    }

    return after_wildcard;
}

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

t_token *merge_tokens(t_token *before, t_token *expanded, t_token *after) {
    t_token *merged = NULL;
    t_token *temp;

    // Adicionar tokens antes do wildcard
    while (before) {
        t_token *new_token = create_token(before->str);
        if (new_token)
            add_token(&merged, new_token);
        before = before->next;
    }

    // Adicionar tokens expandidos
    while (expanded) {
        t_token *new_token = create_token(expanded->str);
        if (new_token)
            add_token(&merged, new_token);
        expanded = expanded->next;
    }

    // Adicionar tokens após o wildcard
    while (after) {
        t_token *new_token = create_token(after->str);
        if (new_token)
            add_token(&merged, new_token);
        after = after->next;
    }

    return merged;
}

t_token *expand_wildcards_in_tokens(t_token *tokens) {
    t_token *expanded_tokens = NULL;
    t_token *current = tokens;

    while (current) {
        if (strchr(current->str, '*')) {
            t_token *before = tokens;
            t_token *after = split_tokens(&tokens, current);
            t_token *expanded = expand_wildcard(current->str);
            expanded_tokens = merge_tokens(before, expanded, after);
            free_tokens(expanded); // Liberar tokens expandidos
            free_tokens(after); // Liberar tokens após o wildcard
            tokens = expanded_tokens; // Atualizar tokens
        }
        current = current->next;
    }

    return tokens;
}
*/
