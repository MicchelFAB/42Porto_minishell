#include "minishell.h"

void	exec_builtin(char **cmd, int *fd, t_shell *shell)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		pwd_cmd();
	else if (!ft_strcmp(cmd[0], "echo"))
		echo_cmd(cmd + 1);
	else if (!ft_strcmp(cmd[0], "cd"))
		cd_cmd(cmd + 1, shell);
	else if (!ft_strcmp(cmd[0], "export"))
	{
		if (!cmd[1])
			print_export(shell);
		else
			export_cmd(cmd + 1, shell);
	}
	else if (!ft_strcmp(cmd[0], "exit"))
		exit_cmd(cmd, fd, shell);
	else if (!ft_strcmp(cmd[0], "unset"))
		unset_cmd(cmd + 1, shell);
	else if (!ft_strcmp(cmd[0], "env"))
	{
		if (cmd[1] == NULL)
			print_cmdenv(shell);
	}
}

int	is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd[0], "export"))
		return (1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd[0], "env"))
		return (1);
	return (0);
}
