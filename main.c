/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:44:15 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/20 15:39:13 by jazevedo         ###   ########.fr       */
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
	//t_tree	*tree;

	//tree = (t_tree){0};
	if (!tokens || !check_tokens(tokens))
		return ;
	main->tokens = tokens;
	if (!is_there_heredoc(main->tokens))
		return ;
	controller(main, main->tokens->first->cmd_args);
	//tree = build_tree(main->tokens);
	//| Executar a árvore.
	free_tokens(&main->tokens);
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

/*
Example: echo a || echo b && echo c | cat -e > txt.txt
	Na árvore: 1: '&&' ou '||', depois '|' e, por fim '<', '<<', '>>' e '>'.

- Procurar nos nodes se tem '&&' ou '||', de trás para frente.
	Se tiver, tudo depois do '&&' ou '||', fica do lado direito da árvore
		e tudo que estiver antes fica do lado esquerda.
{
	Lado Esquerdo: echo a || echo b
	{
		Lado Esquerdo: echo a
		Bifurcação: ||
		Lado Direito: echo b
	}
	Bifurcação: &&
	Lado Direito: echo c | cat -e > txt.txt
}

- Procurar se tem '|' nos nodes já bifurcados.
	Node 1: echo a
	Node 2: ||
	Node 3: echo b
	Não tem '|'.

	Do outro lado tem '|', então bifurcaremos.
	echo b | cat -e > txt.txt
	Logo:
	{
		Lado Esquerdo: echo b
		Bifurcação: '|'
		Lado Direito: cat -e > txt.txt
	}

- Por último, vamos procurar os REDIRs, são eles '<', '<<', '>>' e '>'.
	De um lado não temos REDIRs, mas do outro:
	cat -e > txt.txt
	Logo:
	{
		Lado Esquerdo: cat -e
		Bifurcação: >
		Lado Direito: txt.txt
	}

*/
