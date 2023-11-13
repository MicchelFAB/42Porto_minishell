/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:01:30 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/06 16:01:32 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

void	ft_ctrlc_exec(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
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
	printf("%s:command not found\n", cmd[0]);
	free_split(env);
	free_split(cmd);
	clean_all(shell);
	exit(127);
}
