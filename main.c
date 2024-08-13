/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:25:02 by jazevedo          #+#    #+#             */
/*   Updated: 2024/08/13 15:41:23 by btaveira         ###   ########.fr       */
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
	t_tree	*tree;

	if (!tokens || !check_tokens(tokens))
	{
		free_tokens(&tokens);
		return ;
	}
	main->tokens = tokens;
	if (!is_there_heredoc(main->tokens))
	{
		free_tokens(&main->tokens);
		return ;
	}
	main->tokens = expander(main, main->tokens); //LEAK
	tree = build_tree(main->tokens);
	if (!tree)
	{
		free_tokens(&main->tokens);
		return ;
	}
	main->tree = tree;
	//free_everything(main);
	//exit(1);
	exec(main, main->tree); //LEAK
	free_tokens(&main->tokens);
	free_tree(&main->tree);
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
/*
Casos para tratar:
- Arrumar as aspas do delimitador do Heredoc. | Arrumei.
- Arrumar os Signals dentro do Heredoc.
- cat + ctrlC = last_status(130);. Atualmente está last_status(2);
- cat + ctrl\ = err(GREY"Quit (core dumped)"RESET); + last_status(131);
- Leak nas expansões.
*/
