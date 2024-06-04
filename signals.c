#include "minishell.h"


volatile sig_atomic_t g_status = 0;

void handle_sigint(int sig)
{
    if (sig == SIGINT) // Verifica se o sinal recebido é SIGINT
    {
        if (RL_ISSTATE(RL_STATE_READCMD)) // Verifica se o Readline está em estado de leitura de comando
        {
            if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1) // Injeta um '\n' na entrada padrão (simula a tecla Enter)
            {
                perror("ioctl");
                g_status = 1; // Atualiza o status global para indicar erro
                return;
            }
        }
        else
        {
            if (write(STDIN_FILENO, "\n", 1) == -1) // Escreve um '\n' na entrada padrão
            {
                perror("write");
                g_status = 1; // Atualiza o status global para indicar erro
                return;
            }
        }
        rl_replace_line("", 1); // Substitui a linha atual de entrada por uma linha vazia
        rl_on_new_line(); // Move o cursor para a nova linha
        //rl_redisplay(); // Redisplay para garantir que a linha é atualizada
    }
    return;
}

void start_signals(void)
{
    struct sigaction sig;

    sig.sa_handler = handle_sigint;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = SA_RESTART; // Garante que chamadas interrompidas sejam reiniciadas
    sigaction(SIGINT, &sig, NULL);

    signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT
    signal(SIGTSTP, SIG_IGN); // Ignorar SIGTSTP (Ctrl+Z)
}
