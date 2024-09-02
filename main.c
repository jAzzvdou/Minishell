/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:25:02 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/02 16:00:28 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

volatile int	g_status;

char	*user_input(void)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
		input = ft_strdup("exit");
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

void	parser(t_main *main, t_tokens *tokens)
{
	t_tokens	*tmp;

	if (!tokens || !check_tokens(tokens))
	{
		free_tokens(&tokens);
		return ;
	}
	if (!is_there_heredoc(tokens))
	{
		free_tokens(&tokens);
		return ;
	}
	tmp = expander(main, tokens);
	main->tokens = tmp;
	main->tree = build_tree(tmp);
	if (!main->tree)
	{
		free_tokens(&main->tokens);
		return ;
	}
	exec(main, main->tree);
	free_tree2(main->tree);
}

int	main(int argc, char **argv, char **envp)
{
	t_main	main;

	(void)argv;
	if (argc != 1)
		return (error_argc());
	main = (t_main){0};
	start_env(&main, envp);
	start_pwd(&main);
	start_signals();
	last_status(0);
	while (1)
	{
		g_status = 0;
		parser(&main, tokenizator(user_input()));
	}
	rl_clear_history();
	return (0);
}
