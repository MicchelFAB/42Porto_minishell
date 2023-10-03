/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/03 15:50:27 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int g_signal_exit;

void ft_freetree(t_tree *tree)
{
	t_tree *tmp;

	while (tree)
	{
		tmp = tree;
		tree = tree->next;
		free(tmp->str1);
		free(tmp);
	}
}

void ft_freeshell(t_shell *shell)
{
	ft_freeenv(shell->env);
	ft_freetree(shell->tree);
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
<<<<<<< HEAD
	ft_import_exp(env, shell);
=======
>>>>>>> 92ed04a (03.10.23)
	return (shell);
}

void ft_freetree(t_tree *tree)
{
	t_tree *tmp;

	while (tree)
	{
		tmp = tree;
		tree = tree->next;
		free(tmp->str1);
		free(tmp);
	}
}

void ft_freeshell(t_shell *shell)
{
	ft_freeenv(shell->env);
	ft_freetree(shell->tree);
	free(shell);
}

void	loop_shell(t_shell *shell)
{
	while (true)
	{
		ft_comand_signal();
		shell->line = readline("minishell -> ");
		if (!shell->line || !ft_strlen(shell->line) || ft_chk_char(shell->line))
		{
			if (shell->line)
			{
				free(shell->line);
				continue ;
			}
			else
			{
				free(shell->line);
				ft_freeshell(shell);
				ft_printf("exit\n");
				exit(0);
			}
		}
		add_history(shell->line);
		start_cmd(shell);
<<<<<<< HEAD
		parse_execute(shell);
		wait(0);
=======
>>>>>>> 92ed04a (03.10.23)
		// free(shell->line);
		// ft_putstr_fd("exit\n", 2);
		// break ;
	}
	ft_freeshell(shell);
	exit(g_signal_exit);
<<<<<<< HEAD
=======
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
	while(list->tree)
	{
		printf("%s - %i\n",list->tree->str1, list->tree->type);
		free(list->tree->str1);
		list->tree = list->tree->next;
	}
	free(list->tree);
>>>>>>> 92ed04a (03.10.23)
}



int	main(int ac, char **av, char **env) // ac = argument count, av = argument vector, env = environment
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = init_shell(env);
<<<<<<< HEAD
=======
	print_start_minishell();
>>>>>>> 92ed04a (03.10.23)
	loop_shell(shell);
	return (0);
}