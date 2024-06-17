/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:33:11 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/17 10:58:02 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//----------| LIBRARIES |----------//
# include <unistd.h> // WRITE, ACCESS, PIPE, FORK, WAIT, WAITPID, EXECVE, DUP2
# include <stdlib.h> // MALLOC, FREE, NULL
# include <fcntl.h>  // OPEN, CLOSE
# include <stdio.h>  // PRINTF
# include <string.h> // PERROR
# include <signal.h> // SIGNAL
# include <limits.h> // LIMITS
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

//----------| DEFINES |----------//
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
# define PROMPT \
	RED"m"ORANGE"i"YELLOW"n"GREEN"i"CYAN"s"BLUE"h"LILAC"e"PURPLE"l"BROWN"l"GREY"$ "WHITE

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
}	e_type;

typedef struct s_node
{
	e_type		type;
	char		*cmd;
	char		**cmd_args; //| MALLOCADO
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_tokens
{
	int	size;
	t_node	*first;
	t_node	*last;
}	t_tokens;

typedef struct s_env
{
	int		declare_x;
	char		*name;  //| MALLOCADO
	char		*value; //| MALLOCADO
	char		*line;  //| MALLOCADO
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	char		*pwd;     //| MALLOCADO
	char		*old_pwd; //| MALLOCADO
	t_env		*env;     //| MALLOCADO
	t_tokens	*tokens;  //| MALLOCADO
}	t_main;

//----------| ERRORS |----------//
int	error_argc(void);
int	error_syntax(char *cmd, int option);
void	error_env(char *cmd);
void	error_exit(char *token, int option);
void	*error_closed(void);

//----------| SIGNALS |----------//
void	start_signals(void);

//----------| BUILTINS |----------//
void	controller(t_main *main, char **token);
//__________ env __________
void	env_cmd(t_main *main, char **token);
void	start_env(t_main *main, char **envp);
void	add_env(t_env **env, char *line,int declare_x);
//__________ pwd __________
void	start_pwd(t_main *main);
//__________ echo __________
void	echo_cmd(char **token);
//__________ exit __________
void	exit_cmd(char **token);
//__________ export __________
void	export_cmd(t_main *main, char **token);
//__________ unset _________
void	unset_cmd(t_main *main, char **token);
//__________ cd __________
int	cd_cmd(t_main *main, char **token);
//----------| FUNCTIONS |----------//
//__________ tokens __________
int	check_tokens(t_tokens *tokens);
t_tokens	*tokenizator(char *user_input);
//__________ heredoc __________
int	is_there_heredoc(t_tokens *tokens);

//----------| CLEANERS |----------//
void	free_matrix(char ***matrix);

//----------| UTILS |----------//
//__________ number __________
int	is_number(int nb);
int	only_number(char *s);
int	is_long(char *argv);
long long	ft_atoll(const char *nptr);
char	*ft_itoa(int n);
//__________ space __________
int	is_space(int c);
void	skip_spaces(char **s);
//__________ quote __________
int	is_quote(char *cmd, int i);
int	verify_quote(char *cmd, int i);
int	skip_quotes(char **s);
int	closed_quotes(const char *s);
char	*remove_quote(char *trim, char quote);
//__________ parenthesis __________
int	closed_parenthesis(char *s);
int	verify_parenthesis(char *input, int i);
int	skip_parenthesis(char *input, int i);
//__________ string __________
size_t	ft_strlen(const char *str);
int	ft_isalpha(int c);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	**spliter(char *cmd);
char	**split_input(char *input);

//| TESTES
void	print_tokens(t_tokens *tokens);
#endif //| MINISHELL_H
