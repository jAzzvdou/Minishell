/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:44:15 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/26 14:42:21 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/minishell.h"

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
	if (!is_there_heredoc(main->tokens))
		return ;
	tree = build_tree(main->tokens);
	if (!tree)
		return ;
	main->tree = tree;
	print_tree(main->tree, 0); //| Printar a árvore.
	//exec(main, main->tree);  //| Fazer a execução da árvore.
	builtins(main, token_to_args(main->tokens));
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
		parser(&main, tokenizator(user_input()));
	rl_clear_history();
	return (0);
}

//| Fazer expansão de *.
//| Fazer expansão de $ (lembrar de tratar $0).
//| Arrumar token_to_args();.
//| Fazer make_pipe();.
//| Fazer make_redirs();.
//| Fazer re_exec();.
