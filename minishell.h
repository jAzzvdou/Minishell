#ifndef MINISHELL_H
# define MINISHELL_H

//----------| LIBRARIES |----------//
# include <unistd.h> // WRITE, ACCESS, PIPE, FORK, WAIT, WAITPID, EXECVE, DUP2
# include <stdlib.h> // MALLOC, FREE, NULL
# include <fcntl.h>  // OPEN, CLOSE
# include <stdio.h>  // PRINTF
# include <string.h> // PERROR
# include <signal.h> // SIGNAL
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

//----------| ERRORS |----------//

//----------| STRUCTS |----------//

//----------| FUNCTIONS |----------//

//----------| UTILS |----------//
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);

#endif //| MINISHELL_H
