/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:02:28 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/13 18:22:28 by bmonteir         ###   ########.fr       */
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
	int		i;

	i = 0;
	if (name->shell->line)
		free(name->shell->line);
	while (1)
	{
		name->shell->line = readline("> ");
		if (!name->shell->line)
			print_error("here-document delimited by end-of-file", 0, "warning");
		else if (ft_strcmp(name->shell->line, name->name))
		{
			name->shell->line = ft_expand_env(name->shell);
			i = ft_heredoc_loop2(name->shell->line);
			continue ;
		}
		if (name->shell->line)
			free(name->shell->line);
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
	free(tmp->name);
	ft_free_heredoc(tmp->shell);
	close_fd();
	return (i);
}

void	ft_heredoc_open(t_shell *shell, t_tree *tmp)
{
	t_heredoc	heredoc;

	if (!tmp->next)
		return ;
	heredoc.name = ft_strdup(tmp->next->str1);
	heredoc.shell = shell;
	ft_signals_heredoc(&heredoc);
	ft_start_heredoc(&heredoc);
	free(tmp->next->str1);
	free(heredoc.name);
	tmp->next->str1 = ft_strdup(".heredoc");
	tmp->next->type = FILE;
}

void	ft_start_heredoc(t_heredoc *tmp)
{
	int		pid;
	int		status;
	int		fd;

	pid = fork();
	fd = 0;
	if (pid == 0)
	{
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
