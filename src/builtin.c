#include "../inc/minishell.h"

void	exec_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd_cmd();
	else if (ft_strcmp(cmd[0], "echo") == 0)
		echo_cmd(cmd + 1);
}

int		is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	return (0);
}