#include "../inc/minishell.h"

void	clean_all(t_shell *shell)
{
	//free tokens!!!!
	if (shell->env)
		ft_freeenv(shell->env);
	if (shell->exp)
		ft_freeexp(shell->exp);
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
