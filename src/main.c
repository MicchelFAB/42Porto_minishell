/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/12 18:21:34 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @param void is what the function receives.
 * @param sigaction is a structure that contains the signal handler.
 * @brief 
 * ft_ignore_signal() is a function that ignores the signal.
 * ignore.sa_handler = SIG_IGN; is a signal handler that ignores the signal.
 * sigemptyset(&ignore.sa_mask); is a function that initializes the signal set.
 * ingore.sa_flags = 0; is a flag that specifies the set of signals to be blocked, is set to 0 so that no signals are blocked.
 * sigaction(SIGINT, &ignore, NULL); is a function that changes the action taken by a process on receipt from CTRL+C.
 * sigaction(SIGTSTP, &ignore, NULL); is a function that changes the action taken by a process on receipt from CTRL+Z.
 * sigaction(SIGQUIT, &ignore, NULL); is a function that changes the action taken by a process on receipt from CTRL+\.
 * @return 
*/
void	ft_ignore_signal(void)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	
	sigaction(SIGINT, &ignore, NULL);
	sigaction(SIGTSTP, &ignore, NULL);
	sigaction(SIGQUIT, &ignore, NULL);
	sigaction(11, &ignore, NULL);
	
}
	

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
		if (!line || !ft_strcmp(line, "exit"))
		{
			free(line);
			free(shell);
			ft_printf("exit\n");
			exit(0);
		}
		ft_printf("%s\n", line);
		free(line);
	}
}

int	main(int ac, char **av, char **env) // ac = argument count, av = argument vector, env = environment
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	ft_ignore_signal();
	shell = init_shell(env);
	loop_shell(shell);
	return (0);
}
