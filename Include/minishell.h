#ifndef MINISHELL_H
# define MINISHELL_H

//----------| LIBRARIES |----------//
# include <unistd.h>   // WRITE, ACCESS, PIPE, FORK, WAIT, WAITPID, EXECVE, DUP2
# include <stdlib.h>   // MALLOC, FREE, NULL
# include <fcntl.h>    // OPEN, CLOSE
# include <stdio.h>    // PRINTF
# include <string.h>   // PERROR
# include <signal.h>   // SIGNAL
# include <limits.h>   // LIMITS
# include <sys/wait.h> // WAITPID
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>   // DIR, OPENDIR, READDIR, CLOSEDIR

//----------| DEFINES |----------//
//__________ colors __________
# define RED	"\001\033[38;2;255;0;0m\002"
# define GREEN	"\001\033[38;2;0;255;0m\002"
# define BLUE	"\001\033[38;2;0;0;255m\002"
# define YELLOW	"\001\033[38;2;255;255;0m\002"
# define WHITE	"\001\033[38;2;255;255;255m\002"
# define BLACK	"\001\033[38;2;0;0;0m\002"
# define GREY	"\001\033[38;2;128;128;128m\002"
# define BROWN	"\001\033[38;2;150;75;0m\002"
# define ORANGE	"\001\033[38;2;255;165;0m\002"
# define PURPLE	"\001\033[38;2;153;51;153m\002"
# define LILAC	"\001\033[38;2;200;162;200m\002"
# define PINK	"\001\033[38;2;255;203;219m\002"
# define BMPINK	"\001\033[38;2;255;145;175m\002"
# define CYAN	"\001\033[38;2;0;255;255m\002"
# define RESET	"\033[0m"
# define CLEAR	"\033[H\033[J"
//__________ prompt __________

# define PROMPT "🗿\001\033[38;2;255;0;0m\002m\
\001\033[38;2;255;165;0m\002i\
\001\033[38;2;255;255;0m\002n\
\001\033[38;2;0;255;0m\002i\
\001\033[38;2;0;255;255m\002c\
\001\033[38;2;0;0;255m\002h\
\001\033[38;2;200;162;200m\002a\
\001\033[38;2;153;51;153m\002d\
\001\033[38;2;150;75;0m\002!\
\001\033[38;2;128;128;128m\002🗿 \001\033[38;2;255;255;255m\002"

//----------| GLOBAL |----------//
extern volatile int	g_status;

//----------| STRUCTS |----------//
typedef enum type
{
	CMD,
	BLOCK,
	HEREDOC,
	OR,
	AND,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND
}	t_type;

typedef struct s_node
{
	t_type			type;
	char			*cmd;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_tokens
{
	int		size;
	t_node	*first;
	t_node	*last;
}	t_tokens;

typedef struct s_tree
{
	t_type			type;
	int				fd;
	t_tokens		*exe;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_env
{
	int				declare_x;
	char			*name;
	char			*value;
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	char		*pwd;
	char		*old_pwd;
	t_env		*env;
	t_tokens	*tokens;
	t_tree		*tree;
}	t_main;

//----------| ERRORS |----------//
void		err(char *s);
int			error_argc(void);
int			error_syntax(char *cmd, int option);
void		error_env(char *cmd);
void		error_exit(char *token, int option);
void		*error_closed(void);

//----------| SIGNALS |----------//
void		start_signals(void);

//----------| BUILTINS |----------//
int			last_status(int new_status);
int			builtins(t_main *main, char **token);
//__________ env __________
void		env_cmd(t_main *main, char **token);
void		start_env(t_main *main, char **envp);
void		add_env(t_env **env, char *line, int declare_x);
void		update_env(t_env **env, char *name, char *value);
char		*env_value(t_env *env, char *name);
//__________ pwd __________
void		start_pwd(t_main *main);
//__________ echo __________
void		echo_cmd(char **token);
//__________ exit __________
void		exit_cmd(t_main *main, char **token);
//__________ export __________
void		export_cmd(t_main *main, char **token);
t_env		*alphabetical_env(t_env *tmp);
void		handle_no_args(t_env *env);
void		err_equal_sign(char *token);
int			is_valid_identifier(char *token);
void		up_env_var(t_env *env_var, char *equals_sign, char *token);
void		add_new_env_var(t_main *main, char *token, char *equals_sign);
void		handle_equal_sign(t_main *main, char *token);
//__________ unset _________
void		unset_cmd(t_main *main, char **token);
//__________ cd __________
int			cd_cmd(t_main *main, char **token);
int			handle_home(t_main *main);
int			handle_tilde(t_main *main, char *token);
int			handle_oldpwd(t_main *main);
int			handle_path(char *path);
void		update_pwd_oldpwd(t_main *main);

//----------| FUNCTIONS |----------//
void		parser(t_main *main, t_tokens *tokens);
//__________ execution __________
void		exec(t_main *main, t_tree *tree);
void		make_if(t_main *main, t_tree *tree);
void		make_pipe(t_main *main, t_tree *pipex);
void		make_redir(t_main *main, t_tree *tree);
void		dup_fd(t_tree *tree, int fd);
void		infile(t_tree *tree);
void		outfile(t_tree *tree);
char		*get_block(t_tokens *exec);
void		re_exec(t_main *main, char *block);
int			env_size(t_env *env);
void		controller(t_main *main, char **tokens);
//__________ tokens __________
int			check_tokens(t_tokens *tokens);
void		add_token(t_tokens *tokens, t_type type, char *line);
t_tokens	*start_tokens(void);
t_tokens	*tokenizator(char *user_input);
void		free_args(char **args, int i);
char		**token_to_args(t_tokens *tokens);
t_node		*is_type1(t_node *last);
t_node		*is_type2(t_node *last);
t_node		*is_type3(t_node *last);
int			is_redir(t_type type);
int			need_transfer(t_tokens *right);
t_tokens	*get_right(t_tokens *tokens, t_node *node);
t_tokens	*get_left(t_tokens *tokens, t_node *node);
t_tokens	*remove_last(t_tokens *right);
t_tokens	*get_from_right(t_tokens *left, t_tokens *right);
t_tokens	*send_to_left(t_tokens *right);
t_tree		*build_tree(t_tokens *tokens);
//__________ heredoc __________
int			is_there_heredoc(t_tokens *tokens);
//__________ expansion __________
t_tokens	*before_wildcard(t_tokens *tokens, t_node *node);
t_tokens	*after_wildcard(t_tokens *tokens, t_node *node);
int			is_match(const char *file, const char *pattern);
t_tokens	*expand_wildcard(t_node *wildcard);
t_tokens	*merge_lists(t_tokens *list1, t_tokens *list2);
t_tokens	*wildcard(t_tokens *tokens);
t_tokens	*expander(t_main *main, t_tokens *tokens);
int			is_var(char *cmd);
int			is_valid(int c);
int			is_separator(char *str, int i);
void		skip_quotes_var(char *cmd, int *i, int *words);
void		skip_dollar_var(char *cmd, int *i, int *words);
void		skip_word_var(char *cmd, int *i, int *words);
void		split_spaces(char **split, char *cmd, int *i, int *j);
char		*skip_spaces_split(char *cmd, int *i);
char		*split_quote(char *cmd, int *i);
char		*split_dollar(char *cmd, int *i);
char		*split_word(char *cmd, int *i);
char		**split_variable(char *cmd);
char		*expand_bonus(t_main *main, char *cmd);
char		**split_bonus(char *cmd);
char		*change_var(t_main *main, char *var);
char		*concatenator(char **matrix);

//----------| CLEANERS |----------//
void		free_var(char *name);
void		free_matrix(char **matrix);
void		free_env(t_env **env);
void		free_tokens(t_tokens **tokens);
void		free_tokens2(t_tokens *tokens);
void		free_tree(t_tree **tree);
void		free_tree2(t_tree *tree);
void		free_everything(t_main *main);
void		free_exit(t_main *main, char **env, char **tokens, char *cmd);

//----------| UTILS |----------//
//__________ number __________
int			is_number(int nb);
int			only_number(char *s);
int			is_long(char *argv);
long long	my_atoll(const char *nptr);
char		*my_itoa(int n);
//__________ space __________
int			is_space(int c);
void		skip_spaces(char **s);
//__________ quote __________
int			is_quote(char *cmd, int i);
int			verify_quote(char *cmd, int i);
int			skip_quotes(char **s);
int			closed_quotes(const char *s);
char		*remove_quote(char *trim, char quote);
//__________ parenthesis __________
int			closed_parenthesis(char *s);
int			verify_parenthesis(char *input, int i);
int			skip_parenthesis(char *input, int i);
//__________ string __________
size_t		my_strlen(const char *str);
int			my_isalpha(int c);
int			can_continue(int c);
int			my_strcmp(const char *s1, const char *s2);
int			my_strncmp(const char *s1, const char *s2, size_t n);
char		*my_strchr(const char *s, int c);
char		*my_strdup(const char *s);
char		*my_strndup(const char *s, int n);
char		*my_strtrim(char const *s1, char const *set);
char		*my_strjoin(char const *s1, char const *s2);
char		*my_substr(char const *s, unsigned int start, size_t len);
char		**my_split(char const *s, char c);
char		**spliter(char *cmd);
int			count_words(char *input);
char		**split_input(char *input);

#endif //| MINISHELL_H
