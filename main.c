/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:44:15 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/17 23:02:08 by jazevedo         ###   ########.fr       */
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

//----------| COMEÇO DA ÁRVORE |----------//
int	split_node(t_tree *tree, t_tokens *tokens, t_node *node)
{
	(void)tree;
	(void)tokens;
	(void)node;
}

void	make_roots(t_tree *tree, t_tokens *tokens)
{
	if (!split_node(tree, tokens, is_and_or(tokens))
		return ;
	if (!split_node(tree, tokens, is_pipe(tokens)))
		return ;
	if (!split_node(tree, tokens, is_edir(tokens)))
		return ;
	tree->type = EXE;
	tree->execution = tokens;
}

t_tree	build_tree(t_tokens *tokens)
{
	t_tree	tree;

	tree = (t_tree){0};
	make_roots(&tree, tokens);
	return (tree);
}
//----------|---------------|----------//

void	parser(t_main *main, t_tokens *tokens)
{
	t_tree	*tree;

	tree = (t_tree){0};
	if (!tokens || !check_tokens(tokens))
		return ;
	main->tokens = tokens;
	if (!is_there_heredoc(main->tokens))
		return ;
	controller(main, main->tokens->first->cmd_args);
	tree = build_tree(main->tokens);
	//| Executar a árvore.
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
