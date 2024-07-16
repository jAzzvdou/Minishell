
#include "../Include/minishell.h"

void	infile(t_tree *tree)
{
	char	*file;

	file = tree->right->exe->first->cmd;
	tree->fd = open(file, O_RDONLY);
	if (!access(file, F_OK) && access(file, W_OK | R_OK)) //| Caso não possa escrever ou nem ler do arquivo.
        {
                err(GREY"minichad: Permission denied\n"RESET);
                last_status(1);
        }
        else if (access(file, F_OK)) //| Caso não ache o arquivo.
        {
                err(GREY"minichad: No such file or directory\n"RESET);
                last_status(1);
        }
}

void	outfile(t_tree *tree)
{
	char	*file;

	file = tree->right->exe->first->cmd;
	if (tree->type == OUTPUT)
		tree->fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 00700); //| Substitui o que tem dentro.
	else if (tree->type == APPEND)
		tree->fd = open(file, O_CREAT | O_RDWR | O_APPEND, 00700); //| Adiciona no final do arquivo.
	//| Verificar as permissões do arquivo para ver se é possível escrever ou ler ele.
	if (!access(file, F_OK) && access(file, W_OK | R_OK)) //| Caso não possa escrever ou nem ler do arquivo.
	{
		err(GREY"minichad: Permission denied\n"RESET);
		last_status(1);
	}
	else if (access(file, F_OK)) //| Caso não ache o arquivo.
	{
		err(GREY"minichad: No such file or directory\n"RESET);
		last_status(1);
	}
}

void	set_redir(t_main *main, t_tree *tree)
{
	e_type	type;

	type = tree->left->type;
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HEREDOC)
		set_redir(main, tree->left); //| Caso o LEFT seja REDIR também.
	type = tree->type;
	if ((type == OUTPUT || type == APPEND)
		&& (tree->left->fd >= 0 || !last_status(-1))) //| OUTFILE caso o seput dos REDIRs esteja certo.
	{
		outfile(tree); //| EM FASE DE TESTES.
		if (tree->fd >= 0)
		{
			dup2(tree->fd, STDOUT_FILENO);
			close(tree->fd);
		}
	}
	//| CASO Tree->left->fd == -1, tem que setar o atual para -1.
	else if (tree->left->fd < 0) //| DEU ERRADO.
		tree->fd = -1;
	else if ((type == INPUT || type == HEREDOC)
		 && (tree->left->fd >= 0 || !last_status(-1)))
	{
		infile(tree); // FAZER INPUT E HEREDOC.
		if (tree->fd >= 0)
		{
			dup2(tree->fd, STDIN_FILENO);
			close(tree->fd);
		}
		if (tree->type == HEREDOC)
			unlink(tree->right->exe->first->cmd);
	}
}

void	make_redir(t_main *main, t_tree *tree)
{
	int		in;
	int		out;
	//static int	backup[3];

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	//printf("tree->fd == %d\n", tree->fd);
	set_redir(main, tree);
	if (tree->fd >= 0 || !last_status(-1))
	{
		//backup[0] = in;
		//backup[1] = out;
		//backup[2] = tree->fd;
		exec(main, tree->left); //| DEU CERTO ENTÃO EXECUTA.
	}
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
}
