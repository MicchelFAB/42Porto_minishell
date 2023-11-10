/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:50:33 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/10 12:26:08 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

void	ft_ctrlc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_exit = 130;
}

void	ft_heredoc_ctrlc(int sig, t_heredoc *shell)
{
	static t_heredoc	*tmp;

	if (sig == -1)
		tmp = shell;
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_signal_exit = 130;
		ft_free_heredoc(tmp->shell);
		free(tmp->name);
		close_fd();
		exit(g_signal_exit);
	}
}
// {
// 	(void)sig;
// 	g_signal_exit = 130;
// 	ft_putstr_fd("\n", 2);
// 	close_fd();
// 	exit(g_signal_exit);
// }

/**
 * @brief This function is used to ignore the signal SIGQUIT and to handle the
 * signal SIGINT.
 * 
*/
void	ft_comand_signal(void)
{
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_d(t_shell *shell)
{
	g_signal_exit = 0;
	ft_printf("exit\n");
	ft_freeshell(shell);
	close_fd();
	exit(g_signal_exit);
}

void	update_signal(int pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, status, 0);
	ft_comand_signal();
}
