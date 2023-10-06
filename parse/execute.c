#include "../inc/minishell.h"

void	execute(char **cmd, int *fd, int *std_in, t_shell *shell)
{
	(void)fd;
	(void)std_in;
	if (is_builtin(cmd))
		exec_builtin(&cmd[0], shell);
}