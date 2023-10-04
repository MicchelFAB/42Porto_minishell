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

int		g_signal_exit;

void ft_ctrlc(int sig)
{
	(void)sig;
	g_signal_exit = 130;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @brief This function is used to ignore the signal SIGQUIT and to handle the
 * signal SIGINT.
 * 
*/
void	ft_comand_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrlc);	
}

// init_shell() is a function that allocates memory for the shell structure and
// initializes the environment variable.
void init_shell(t_shell *shell, char **env)
{
	shell->line = NULL;
	ft_import_env(shell, env);
	ft_import_exp(env, shell);
	// shell->exp = ft_import_exp(&shell, env);
}

void	loop_shell(t_shell *shell)
{
	char	**cmd;

	while (true)
	{
		ft_comand_signal();
		shell->line = readline("minishell -> ");
		cmd = ft_split(shell->line, ' ');
		if (!shell->line)
		{
			free(shell->line);
			ft_freeenv(shell->env);
			ft_printf("exit\n");
			exit(0);
		}
		else 
		{
			add_history(shell->line);
			start_cmdenv(shell);
		}
		if (is_builtin(cmd))
			exec_builtin(cmd, shell);
		//ft_printf("%s\n", shell->line);
		free(shell->line);
	}
}

// ft_debug_terminal() is a function that prints the terminal name.

int	main(int ac, char **av, char **env) // ac = argument count, av = argument vector, env = environment
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell(&shell, env);
	loop_shell(&shell);
	return (0);
}