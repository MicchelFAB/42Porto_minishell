/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:50:33 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/02 15:29:18 by mamaral-         ###   ########.fr       */
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

void	ft_heredoc_ctrlc(int sig)
{
	(void)sig;
	g_signal_exit = 130;
	ft_putstr_fd("\n", 2);
	exit(g_signal_exit);
}

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
	ft_freeshell(shell);
	ft_printf("exit\n");
	exit(0);
}

void	update_signal(int pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, status, 0);
	ft_comand_signal();
}