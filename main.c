/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaveira <btaveira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:44:15 by jazevedo          #+#    #+#             */
/*   Updated: 2024/07/12 14:55:28 by jazevedo         ###   ########.fr       */
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
		return ;
	main->tokens = tokens;
	if (!is_there_heredoc(main->tokens)) //| Tratar as aspas do Delimiter.
		return ;
	main->tokens = expander(main->tokens); //| Vamos expandir aqui, vai ser melhor para a execução.
	tree = build_tree(main->tokens);
	if (!tree)
		return ;
	main->tree = tree;
	exec(main, main->tree);
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
	while (1)
	{
		g_status = 0;
		//last_status(0);
		parser(&main, tokenizator(user_input()));
		//printf("last status: %d\n", last_status(-1));
	}
	rl_clear_history();
	return (0);
}

/*
Casos para tratar:
- Arrumar o export e o unset (pequenos erros).
- Arrumar os Signals dentro do Heredoc. Além disso temos que fazer os REDIRS para o Heredoc funcionar corretamente.
- cat + ctrlC = last_status(130);. Atualmente está last_status(2);
- cat + ctrl\ = err(GREY"Quit (core dumped)"RESET); + last_status(131);
*/
