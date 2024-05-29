#include "minishell.h"

int	error_argc(int nb)
{
	printf(RED"Error!\n");
	printf(GREY"\tUsage:"YELLOW"./minishell\n");
	return (nb);
}

void	print_newline(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
	}
	return ;
}

void	start_signals(void)
{
	signal(SIGINT, print_newline);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp; //| We need to use this in the future.
	if (argc != 1)
		return (error_argc(1));

	//| Start Signals
	start_signals();

	//| The While True
	char	*input;
	while (1)
	{
		input = readline(GREEN"minishell$ "RESET);
		if (!input)
			input = ft_strdup("exit");
		if (ft_strcmp(input, ""))
		{
			if (!ft_strcmp(input, "exit"))
			{
				printf(ORANGE"exit\n");
				add_history(input);
				free(input);
				break ;
			}
			add_history(input);
		}
	}

	return (0);
}

/*
	BUILTINS:
- echo (with option '-n')
- cd
- pwd
- export
- unset
- env  -> DO THIS NOW (ITS EASY.. I THINK)
- exit -> DONE
*/
