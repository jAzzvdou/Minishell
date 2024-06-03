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
# include <readline/readline.h>
# include <readline/history.h>

//----------| DEFINES |----------//
# define RED	"\033[38;2;255;0;0m"
# define GREEN	"\033[38;2;0;255;0m"
# define BLUE	"\033[38;2;0;0;255m"
# define YELLOW	"\033[38;2;255;255;0m"
# define WHITE	"\033[38;2;255;255;255m"
# define BLACK	"\033[38;2;0;0;0m"	
# define GREY	"\033[38;2;128;128;128m"
# define BROWN	"\033[38;2;150;75;0m"	
# define ORANGE	"\033[38;2;255;165;0m"
# define PURPLE	"\033[38;2;153;51;153m"
# define LILAC	"\033[38;2;200;162;200m"
# define PINK	"\033[38;2;255;203;219m"
# define BMPINK	"\033[38;2;255;145;175m"
# define CYAN	"\033[38;2;0;255;255m"
# define RESET	"\033[0m"
# define CLEAR	"\033[H\033[J"

# define NOFREE	0
# define FREE	1

//----------| STRUCTS |----------//

//----------| ERRORS |----------//
int	error_argc(void);

//----------| SIGNALS |----------//
void	start_signals(void);

//----------| ENVIRONMENT |----------//
void	start_pwd(void);
void	start_env(char **envp);
char	*static_pwd(char *new_pwd, int clear);
char	**static_env(char **new_envp, int clear);

//----------| BUILTINS |----------//
void	env_cmd(char **token);

//----------| FUNCTIONS |----------//
void	controller(char **token);

//----------| CLEANERS |----------//
void	free_matrix(char ***matrix);

//----------| UTILS |----------//
int	only_number(char *s);
int	is_long(char *argv);
int	is_space(int c);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

#endif //| MINISHELL_H
