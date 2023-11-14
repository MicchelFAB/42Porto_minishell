/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:48:20 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/13 18:10:48 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	print_error(char *msg, int error, char *line)
{
	g_signal_exit = error;
	ft_putstr_fd(line, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

void	print_start_minishell(void)
{
	char	ascii[2860];
	int		result;
	int		fd;
	ssize_t	read_bytes;

	fd = open("./.ascii", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	result = read(fd, &ascii, 2860);
	read_bytes = write(1, ascii, result);
	if (read_bytes == -1)
	{
		perror("write");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

// init_shell() is a function that allocates memory for the shell structure and
// initializes the environment variable.
t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(EXIT_FAILURE);
	shell->line = NULL;
	shell->child_proc = 0;
	shell->pid = 0;
	shell->tree = NULL;
	ft_import_env(shell, env);
	ft_import_exp(env, shell);
	return (shell);
}

void	wait_child_proc(t_shell *shell)
{
	int		status;

	if (waitpid(shell->pid, &status, 0) != -1)
	{
		shell->child_proc--;
		if (WIFEXITED(status))
			g_signal_exit = WEXITSTATUS(status);
		shell->pid = 0;
	}
	while (shell->child_proc)
	{
		wait(0);
		shell->child_proc--;
	}
}

int	ft_chk_char(char *line)
{
	int	size;

	size = ft_strlen(line);
	if (check_quote_pair(line, size) || check_special(line)
		|| str_whitespace_only(line))
		return (1);
	return (0);
}
