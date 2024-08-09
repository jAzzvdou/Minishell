/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/09 20:15:10 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*free_function(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (tmp);
}

void	err_heredoc(char *cmd)
{
	err(GREY"minichad: warning: here-document");
	err("at line N delimited by end-of-file (wanted `");
	err(cmd);
	err("')\n"RESET);
	last_status(0);
}

void sig_int_heredoc_handle(int sig)
{
    if (sig == SIGINT)
    {
        signal(SIGINT, SIG_IGN);  // Ignora sinais futuros de SIGINT
        g_status = 130;           // Define status para 130, indicando interrupção pelo SIGINT
        exit(g_status);           // Sai do processo com o status 130
    }
    else
    {
        write(1, "> ", 2);
        ioctl(1, TIOCSTI, 1);     // Simula entrada de caractere para readline
        rl_on_new_line();
        rl_replace_line("", 0);
    }
}

void core_heredoc(int fd, char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline(GREEN"> ");
        
        if (!line)
        {
            err_heredoc(delimiter);
            break;
        }
        
        if (!ft_strcmp(delimiter, line))
        {
            free(line);
            break;
        }

        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
}

// Função adaptada heredoc que usa o sig_int_heredoc_handle
int heredoc(t_node *token, char *file, int fd)
{
    pid_t   hd_pid;
    int     hd_fd[2];
    int     status;

    if (pipe(hd_fd) == -1)
        return (-1);

    signal(SIGINT, SIG_IGN);  // Ignora SIGINT no processo pai
    hd_pid = fork();

    if (hd_pid == 0)  // Processo filho
    {
        close(hd_fd[0]);
        signal(SIGINT, &sig_int_heredoc_handle);  // Configura manipulador de SIGINT
        core_heredoc(hd_fd[1], token->cmd);
        close(hd_fd[1]);
        exit(1);
    }

    // Processo pai
    waitpid(hd_pid, &status, 0);
    close(hd_fd[1]);
    g_status = WEXITSTATUS(status);

    if (g_status == 130)  // Se interrompido pelo SIGINT
    {
        close(hd_fd[0]);
        return (-1);
    }

    close(fd);
    free(token->cmd);
    token->cmd = file;

    return (hd_fd[0]);  // Retorna descritor de arquivo para leitura
}

int start_heredoc(t_node *token, int nb)
{
    int             fd;
    static long int random;
    char            *file;

    random = random + (u_int64_t)start_heredoc * nb;
    file = free_function(ft_strdup("/tmp/heredoc"), ft_itoa(random));
    fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
        return (free(file), 0);
    
    int hd_fd = heredoc(token, file, fd);
    
    if (hd_fd == -1)
        return (0);
    
    return (hd_fd);  // Retorna o descritor de arquivo para leitura
}

int	is_there_heredoc(t_tokens *tokens)
{
	t_node	*token;

	token = tokens->first;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (!start_heredoc(token->next, 42))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
