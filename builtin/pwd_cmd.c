#include "../inc/minishell.h"

/*
getcwd() — Get path name of the working directory
*/

void	pwd_cmd(void)
{
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
}