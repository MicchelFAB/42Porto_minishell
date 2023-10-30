#include "minishell.h"

extern int	g_signal_exit;

void	ft_ctrlc_exec(int sig)
{
	(void)sig;
	printf("\n");
	g_signal_exit = 130;
}

void	ft_ctrl_bslash(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	g_signal_exit = 131;
}

void	ft_exec_signal(void)
{
	signal(SIGINT, ft_ctrlc_exec);
	signal(SIGQUIT, ft_ctrl_bslash);
}

void	error_execve(char **env, char **cmd, t_shell *shell)
{
	free(env);
	free(cmd);
	clean_all(shell);
	printf("command not found\n");
	exit(127);
}
