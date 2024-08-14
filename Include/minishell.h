/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:49 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/14 11:29:05 by btaveira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define PART1	"🗿"RED"m"ORANGE"i"YELLOW"n"GREEN"i"CYAN"c"BLUE"h"
# define PART2	LILAC"a"PURPLE"d"BROWN"!"GREY"🗿 "WHITE
# define PROMPT PART1""PART2

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
int			is_valid_identifier(char *token);
void		up_env_var(t_env *env_var, char *equals_sign, char *token);
void		add_new_env_var(t_main *main, char *token, char *equals_sign);
void		update_existing_env_var(t_env *env_var, char *name, char *token);
void		add_env_var_if_not_found(t_main *main, char *name, char *token);
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
void		re_exec(t_main *main, char *block);
char		*pathfinder(char **env, char *cmd);
void		exec_cmd_directly(char *cmd, char **tokens, char **env);
void		exec_cmd_pathfinder(t_main *main, char *cmd, char **tokens, char **env);
void		handle_child_process(t_main *main, char *cmd, char **tokens, char **env);
void		handle_parent_process(pid_t pid, int *status);
void		controller(t_main *main, char **tokens);
//__________ tokens __________
int			check_tokens(t_tokens *tokens);
void		add_token(t_tokens *tokens, t_type type, char *line);
t_tokens	*start_tokens(void);
t_type		get_token_type(char *str);
void		process_individual_token(t_tokens *tokens, char *token_str);
void		process_split_string(t_tokens *tokens, char **splited);
t_tokens	*tokenizator(char *user_input);
void		free_args(char **args, int i);
char		**token_to_args(t_tokens *tokens);
t_node		*is_type1(t_node *last);
t_node		*is_type2(t_node *last);
t_node		*is_type3(t_node *last);
void		remove_node_from_right(t_node *node, t_tokens *right);
void		add_node_to_tokens(t_node *node, t_tokens *tokens);
void		transfer_nodes(t_tokens *tokens, t_tokens *right);
void		remove_last_node(t_tokens *tokens);
void		addfront_popback(t_tokens *right, t_tokens *tokens);
int			process_non_separator(char *input, int i);
t_tokens	*split_tokens(t_tokens *tokens, t_node *node);
t_tree		*build_tree(t_tokens *tokens);
//__________ heredoc __________
void		err_heredoc(char *cmd);
void		sig_int_heredoc_handle(int sig);
void		handle_heredoc_child_process(t_node *token, int fd);
int			handle_heredoc_parent_process(pid_t hd_pid, char *file, int fd);
int			fork_and_handle_heredoc(t_node *token, char *file, int fd);
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
char		**split_variable(char *cmd);
char		*expand_bonus(t_main *main, char *cmd);
char		**split_bonus(char *cmd);
char		*change_var(t_main *main, char *var);
char		*concatenator(char **matrix);
//---------- execution ----------//
void		exec(t_main *main, t_tree *tree);
//----------| CLEANERS |----------//
void		free_matrix(char **matrix);
void		free_env(t_env **env);
void		free_tokens(t_tokens **tokens);
void		free_tokens2(t_tokens *tokens);
void		free_tree(t_tree **tree);
void		free_everything(t_main *main);

//----------| UTILS |----------//
//__________ number __________
int			is_number(int nb);
int			only_number(char *s);
int			is_long(char *argv);
long long	ft_atoll(const char *nptr);
char		*ft_itoa(int n);
//__________ space __________
int			is_space(int c);
void		skip_spaces(char **s);
int			skip_spaces2(char *input, int i);
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
size_t		ft_strlen(const char *str);
int			ft_isalpha(int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			skip_separator(char *input, int i);
int			is_separator(char *str, int i);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, int n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			calculate_total_length(char **matrix);
void		copy_string_to_new_str(char *new_str, char *str, int *len);
char		**ft_split(char const *s, char c);
char		**spliter(char *cmd);
char		**split_input(char *input);

//| TESTES
void		debug(void);
void		print_tokens(t_tokens *tokens);
void		revprint_tokens(t_tokens *tokens);
void		print_tree(t_tree *tree, int level);

#endif //| MINISHELL_H
