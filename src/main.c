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

// ft_check_signal() is a function that checks if the signal is SIGINT or SIGQUIT.

// int	ft_check_signal(void)
// {
// 	struct sigaction	sa;
// 	int		signal = 0;

// 	sa.sa_handler = SIG_IGN;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	if (sigaction(SIGINT, &sa, NULL) == 1)
// 		signal = SIGINT;
// 	if (sigaction(SIGQUIT, &sa, NULL) == 1)
// 		signal = SIGQUIT;
// 	return (signal);
// }

// init_shell() is a function that allocates memory for the shell structure and
// initializes the environment variable.

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env;
	return (shell);
}

// loop_shell() is a function that loops the shell and prints the prompt.

void	loop_shell(t_shell *shell)
{
	char	*line;

	shell->fd = 0;
	while (true)
	{
		line = readline("minishell -> "); 
		//line = get_next_line(shell->fd);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			exit(0);
		}
		ft_printf("%s\n", line);
		free(line);
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
