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

/*
struct dirent
{
	ino_t		d_ino;       //| Número do inode
	off_t		d_off;       //| Deslocamento
	unsigned short	d_reclen;    //| Comprimento do registro
	unsigned char	d_type;      //| Tipo de arquivo
	char		d_name[256]; //| Nome do arquivo
};
*/

t_tokens	*expand_wildcard(t_node *wildcard)
{
	DIR		*dir;   //| 'DIR' é uma estrutura que representa um diretório aberto.
	struct dirent	*entry; //| Struct comentada acima.
	t_tokens	*expanded;

	expanded = start_tokens();
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		//| Pula os arquivos que começam com '.'.
		if (*(char *)entry->d_name != '.' && is_match((char *)entry->d_name, wildcard->cmd)) //| Caso dê match, adiciona na lista.
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
		//free(list1);?
	}
	if (list2)
	{
		tmp = list2->first;
		while (tmp)
		{
			add_token(new, tmp->type, tmp->cmd);
			tmp = tmp->next;
		}
		//free(list2);?
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
	return (expanded);
}

t_tokens	*expander(t_tokens *tokens)
{
	//t_tokens	*expanded;
	t_tokens	*tmp;

	tmp = wildcard(tokens);          //| Expandir *. QUASE PRONTO!
	//expanded = expansion_var(tmp); //| Expandir VAR.
	//free(tmp);
	//tmp = NULL;
	return (tmp); //| SÓ PARA TESTES, O RETURN CERTO É O DE BAIXO.
	//return (expanded);
}

char *get_env_value(t_env *env, const char *name) {
    while (env) {
        if (strcmp(env->name, name) == 0) {
            return env->value;
        }
        env = env->next;
    }
    return "";
}

void handle_quotes(const char **start, int *in_double_quotes, int *in_single_quotes) {
    if (**start == '"' && !*in_single_quotes) {
        *in_double_quotes = !*in_double_quotes;
        (*start)++;
    } else if (**start == '\'' && !*in_double_quotes) {
        *in_single_quotes = !*in_single_quotes;
        (*start)++;
    }
}

int expand_var(t_main *main, char **expanded, const char **start) {
    if (strncmp(*start, "$$", 2) == 0) {
        return 0; // Indica que encontrou a string $$
    }

    const char *end = *start + 1;
    while (isalnum(*end) || *end == '_') end++;
    char *name = strndup(*start + 1, end - *start - 1);
    char *value = get_env_value(main->env, name);
    strcat(*expanded, value);
    free(name);
    *start = end - 1;
    return 1;
}

char *expand_variables(t_main *main, const char *cmd) {
    char *expanded = malloc(strlen(cmd) * 2 + 1);
    const char *start = cmd;
    int in_double_quotes = 0, in_single_quotes = 0;

    if (!expanded) return NULL;
    expanded[0] = '\0';

    while (*start) {
        handle_quotes(&start, &in_double_quotes, &in_single_quotes);
        if (*start == '$' && !in_single_quotes) {
            if (!expand_var(main, &expanded, &start)) {
                free(expanded);
                return strdup(""); // Retorna uma string vazia para representar o prompt
            }
        } else {
            strncat(expanded, start, 1);
        }
        start++;
    }

    return expanded;
}

void expand_tokens(t_main *main, t_tokens *tokens) {
    t_node *current;
    char *expanded_cmd;

    current = tokens->first;
    while (current) {
        if (current->cmd) {
            expanded_cmd = expand_variables(main, current->cmd);
            if (expanded_cmd) {
                free(current->cmd);
                current->cmd = expanded_cmd;
            }
        }
        current = current->next;
    }
}
