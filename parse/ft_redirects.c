/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:01:37 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/08 09:03:12 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

int	ft_input_redirect(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_signal_exit = 1;
		return (1);
	}
	dup2(fd, IN);
	close(fd);
	return (0);
}

int	ft_output_redirect(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_signal_exit = 1;
		return (1);
	}
	dup2(fd, OUT);
	close(fd);
	return (0);
}

int	ft_output_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_signal_exit = 1;
		return (1);
	}
	dup2(fd, OUT);
	close(fd);
	return (0);
}

int	ft_redir_type(char *name, char *str)
{
	if (ft_strcmp("<", str) == 0)
		return (ft_input_redirect(name));
	else if (ft_strcmp("<<", str) == 0)
		return (ft_heredoc_read(name));
	else if (ft_strcmp(">", str) == 0)
		return (ft_output_redirect(name));
	else if (ft_strcmp(">>", str) == 0)
		return (ft_output_append(name));
	else
		return (0);
}
