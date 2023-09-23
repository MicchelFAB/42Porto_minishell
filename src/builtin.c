#include "../inc/minishell.h"

void	exec_builtin(char **cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		pwd_cmd();
	else if (!ft_strcmp(cmd[0], "echo"))
		echo_cmd(cmd + 1);
	else if (!ft_strcmp(cmd[0], "cd"))
		cd_cmd(cmd + 1, shell);
}

int		is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	return (0);
}