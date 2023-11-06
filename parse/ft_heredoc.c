/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:02:28 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/06 15:42:20 by mamaral-         ###   ########.fr       */
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

static int	ft_heredoc_loop(char *name)
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
		signal(SIGINT, ft_heredoc_ctrlc);
		prompt = readline("> ");
		if (!prompt)
			print_error("here-document delimited by end-of-file", 0, "warning");
		else if (ft_strcmp(prompt, str))
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

int	ft_heredoc_child(char *name, t_shell *shell)
{
	int					i;

	i = 0;
	ft_free_heredoc(shell);
	if (ft_strlen(name) > 9999)
	{
		print_error("EOF too long", 1, "error");
		free(name);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	i = ft_heredoc_loop(name);
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

void	ft_start_heredoc(t_shell *shell, char *tmp)
{
	int		pid;
	int		status;
	int		fd;

	(void)shell;
	pid = fork();
	fd = 0;
	if (pid == 0)
		exit(ft_heredoc_child(tmp, shell));
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
