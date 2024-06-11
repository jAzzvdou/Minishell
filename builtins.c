#include "minishell.h"

void	controller(t_main *main, char **token)
{
	if (!strcmp(token[0], "exit"))
		exit_cmd(token);
	else if (!strcmp(token[0], "env"))
		env_cmd(main, token);
	else if (!strcmp(token[0], "pwd"))
		printf("%s\n", main->pwd);
	else if (!strcmp(token[0], "echo"))
		echo_cmd(token); //| LEMBRAR DE TRATAR '$0' E '$$'.
	else if (!strcmp(token[0], "export")) // arrumar seg fault quando da erro (7=p)
		export_cmd(main, token);
	/*else if (!strcmp(token[0], "unset"))
		unset_cmd(token);
	else if (!strcmp(token[0], "cd"))
		cd_cmd(token);*/
	else if (!strcmp(token[0], "clear")) //| TIRAR FUTURAMENTE
		printf(CLEAR);
}
