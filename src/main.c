/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/18 10:38:29 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_exit;

void	ft_ctrlc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_exit = 130;
}

/**
 * @brief This function is used to ignore the signal SIGQUIT and to handle the
 * signal SIGINT.
 * 
*/
void	ft_comand_signal(void)
{
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_d(t_shell *shell)
{
	ft_freeshell(shell);
	ft_printf("exit\n");
	exit(0);
}

void	loop_shell(t_shell *shell)
{
	while (true)
	{
		ft_comand_signal();
		shell->line = readline("minishell -> ");
		if (!shell->line)
			ctrl_d(shell);
		else if (!ft_strlen(shell->line) || ft_chk_char(shell->line))
			free(shell->line);
		else
		{
			add_history(shell->line);
			start_cmd(shell);
			parse_execute(shell);
			wait(0);
			free(shell->line);
			ft_freetree(shell->tree);
		}
	}
	ft_freeshell(shell);
	exit(g_signal_exit);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = init_shell(env);
	print_start_minishell();
	loop_shell(shell);
	return (0);
}
