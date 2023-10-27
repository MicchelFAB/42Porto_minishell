#include "minishell.h"

extern int		g_signal_exit;

void	clean_all(t_shell *shell)
{
	if (shell->env)
		ft_freeenv(shell->env);
	if (shell->exp)
		ft_freeexp(shell->exp);
	if (shell->line)
		free(shell->line);
	if (shell->tree)
		ft_freetree(shell->tree);
	if (shell)
		free(shell);
	g_signal_exit = 0;
	rl_clear_history();
}

void	free_split(char **ptr)
{
	int		i;

	i = 0;
	while (ptr[i])
		i++;
	while (--i >= 0)
		free(ptr[i]);
	free(ptr);
}
