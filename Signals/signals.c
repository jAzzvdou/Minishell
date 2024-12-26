#include "../Include/minishell.h"

void	err_signal(char *err)
{
	perror(err);
	g_status = 1;
	last_status(130);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
		{
			if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			{
				err_signal("ioctl");
				return ;
			}
		}
		else
		{
			if (write(STDIN_FILENO, "\n", 1) == -1)
			{
				err_signal("write");
				return ;
			}
		}
		last_status(130);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
	return ;
}

void	start_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = handle_sigint;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}
