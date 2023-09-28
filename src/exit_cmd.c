#include "../inc/minishell.h"

void	exit_cmd(char **cmd, t_shell *shell)
{
	int		len;

	len = 0;
	//verificar se é pipe!!!!
	while (cmd[len])
		len++;
	printf("exit\n");
	if (len > 2)
	{
		print_error("too many arguments", 1);
		return ;
	}
}