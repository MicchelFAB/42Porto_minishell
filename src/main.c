/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/10 11:49:09 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal_exit;

void ft_freetree(t_tree *tree)
{
	t_tree *tmp;

	while (tree)
	{
		tmp = tree->next;
		free(tree->str1);
		free(tree);
		tree = tmp;
	}
}

void ft_freeshell(t_shell *shell)
{
	ft_freeenv(shell->env);
	free(shell->line);
	free(shell);
}

void ft_ctrlc(int sig)
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

// init_shell() is a function that allocates memory for the shell structure and
// initializes the environment variable.
t_shell *init_shell(char **env)
{
	t_shell *shell;
	shell = malloc(sizeof(t_shell));
	if(!shell)
		exit(EXIT_FAILURE);
	shell->line = NULL;
	shell->t_count = 0;
	shell->tree = NULL;
	ft_import_env(shell, env);
	return (shell);
}

void ctrl_d(t_shell *shell)
{
		ft_freeshell(shell);
		ft_printf("exit\n");
		exit(0);
}

// loop_shell() is a function that loops the shell and prints the prompt.

void	loop_shell(t_shell *shell)
{
	while (true)
	{
		ft_comand_signal();
		shell->line = readline("minishell -> ");
		if (!shell->line || !ft_strcmp(shell->line, "exit"))
			ctrl_d(shell);
		else if (!ft_strlen(shell->line) || ft_chk_char(shell->line))
			free(shell->line);
		else
		{
			add_history(shell->line);
			start_cmd(shell);
			free(shell->line);
			ft_freetree(shell->tree);
		}
	}
	ft_freeshell(shell);
	exit(g_signal_exit);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	print_start_minishell(void)
{
	char	ascii[2860];
	int		result;
	int		fd;
	ssize_t	read_bytes;

	fd = open("./.ascii", O_RDONLY);
	if (fd == -1) {
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

void ft_print_list(t_shell *list)
{
	t_tree *tmp;
	
	tmp = list->tree;
	while(tmp)
	{
		printf("%s - %i\n",tmp->str1, tmp->type);
		tmp = tmp->next;
	}
	free(tmp);	
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
