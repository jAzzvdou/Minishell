#include "../Include/minishell.h"

void	process(t_main *main, t_tree *pipe, int *fd, int right)
{
	if (!right)
		dup2(fd[1], STDOUT_FILENO);
	else if (right)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (!right)
	{
		exec(main, pipe->left);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	else if (right)
	{
		exec(main, pipe->right);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	free_everything(main);
	exit(last_status(-1));
}

void	waiting(pid_t *pid, int *fd)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	last_status(status);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	last_status(status);
}

void	make_pipe(t_main *main, t_tree *pipex)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd))
		last_status(1);
	else
	{
		pid[0] = fork();
		if (!pid[0])
			process(main, pipex, fd, 0);
		pid[1] = fork();
		if (!pid[1])
			process(main, pipex, fd, 1);
		if (pid[0] < 0 || pid[1] < 0)
			err(GREY"Fork Error\n"RESET);
		close(fd[0]);
		close(fd[1]);
		waiting(pid, fd);
	}
	close(fd[0]);
	close(fd[1]);
}
