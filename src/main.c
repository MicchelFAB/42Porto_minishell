/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/12 09:45:46 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env;
	return (shell);
}

void	loop_shell(t_shell *shell)
{
	shell->fd = 0;
	while (true)
	{
		shell->line = readline("minishell -> ");
		shell->command = ft_split(shell->line, ' ');
		if (ft_strcmp(shell->command[0], "exit") == 0)
		{
			free(shell->line);
			exit(0);
		}
		if (is_builtin(shell->command))
			exec_builtin(shell->command);
		free(shell->line);
		// shell->signal = ft_check_signal();
		// if (shell->signal == SIGINT)
		// 	exit(0);
	}
}

// ft_debug_terminal() is a function that prints the terminal name.

int	main(int ac, char **av, char **env) // ac = argument count, av = argument vector, env = environment
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = init_shell(env);
	loop_shell(shell);
	return (0);
}
