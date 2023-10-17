/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:48:20 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/17 11:42:16 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	print_error(char *msg, int error)
{
	g_signal_exit = error;
	printf("%s\n", msg);
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
	shell->t_count = 0;
	shell->tree = NULL;
	ft_import_env(shell, env);
	ft_import_exp(env, shell);
	return (shell);
}