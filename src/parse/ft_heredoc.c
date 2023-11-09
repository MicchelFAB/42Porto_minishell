/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:02:28 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/09 13:53:10 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

static int	ft_heredoc_loop2(char *s1)
{
	int		tmp;

	tmp = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tmp < 0)
		return (1);
	ft_putendl_fd(s1, tmp);
	close(tmp);
	free(s1);
	return (0);
}

static int	ft_heredoc_loop(t_heredoc *name)
{
	char	*prompt;
	char	str[1000000];
	int		i;

	i = 0;
	ft_memset(str, 0, 1000000);
	ft_memcpy(str, name, strlen(name));
	free(name);
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
			print_error("here-document delimited by end-of-file", 0, "warning");
		else if (ft_strcmp(prompt, name->name))
		{
			i = ft_heredoc_loop2(prompt);
			continue ;
		}
		if (prompt)
			free(prompt);
		break ;
	}
	return (i);
}

int	ft_heredoc_child(t_heredoc *tmp)
{
	int					i;

	i = 0;
	signal(SIGQUIT, SIG_IGN);
	i = ft_heredoc_loop(tmp);
	ft_free_heredoc(tmp->shell);
	close_fd();
	return (i);
}

int	ft_heredoc_read(char *name)
{
	int		tmp;

	tmp = open(name, O_RDONLY);
	if (tmp < 0)
		return (1);
	unlink(name);
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	return (0);
}

void	ft_copy_shell(t_shell *shell, t_heredoc *tmp)
{
	tmp->shell = &*shell;
}

void	ft_start_heredoc(t_shell *shell, t_heredoc *tmp)
{
	int		pid;
	int		status;
	int		fd;

	pid = fork();
	fd = 0;
	if (pid == 0)
	{
		ft_copy_shell(shell, tmp);
		exit(ft_heredoc_child(tmp));
	}
	else
	{
		update_signal(pid, &status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			fd = open(".heredoc", O_WRONLY | O_TRUNC, 0644);
			close(fd);
			g_signal_exit = 130;
		}
	}
}
