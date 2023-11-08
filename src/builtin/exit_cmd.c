/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:51:37 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/08 12:08:50 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	close_fd_exit(int *fd)
{
	close(fd[IN]);
	close(fd[OUT]);
}

void	ft_exit_two_args(char **cmd, int *fd, t_shell *shell)
{
	long long	code_num;

	if (ft_is_number(cmd[1]))
	{
		clean_all(shell);
		code_num = (char)ft_atol(cmd[1]);
		free_split(cmd);
		close_fd_exit(fd);
		exit(code_num);
	}
	else
	{
		print_error("numeric argument required", 2, "minishell: exit");
		g_signal_exit = 2;
		clean_all(shell);
		close_fd_exit(fd);
	}
}

void	exit_cmd(char **cmd, int *fd, t_shell *shell)
{
	int		len;

	len = 0;
	if (contains_pipe(shell))
		return ;
	while (cmd[len])
		len++;
	if (len > 2)
	{
		print_error("too many arguments", 1, "minishell: exit");
		return ;
	}
	if (len == 1)
	{
		close_fd_exit(fd);
		g_signal_exit = 0;
		clean_all(shell);
	}
	if (len == 2)
		ft_exit_two_args(cmd, fd, shell);
	printf("exit\n");
	free_split(cmd);
	exit(g_signal_exit);
}

char	*ft_exit_nbr(void)
{
	char	*nbr;

	nbr = ft_itoa(g_signal_exit);
	return (nbr);
}
