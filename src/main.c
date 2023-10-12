/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/10/16 14:04:31 by mamaral-         ###   ########.fr       */
=======
/*   Updated: 2023/10/04 10:52:21 by mamaral-         ###   ########.fr       */
>>>>>>> 49850c4 (Lexer Leaks removed)
=======
/*   Updated: 2023/10/09 18:44:53 by mamaral-         ###   ########.fr       */
>>>>>>> c9d4cc5 (09-10)
=======
/*   Updated: 2023/10/10 11:49:09 by mamaral-         ###   ########.fr       */
>>>>>>> 8fd3012 (12/10/23)
=======
/*   Updated: 2023/10/12 23:04:28 by mamaral-         ###   ########.fr       */
>>>>>>> bc19d77 (Day End)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_exit;

void	ft_freetree(t_tree *tree)
{
	t_tree	*tmp;

	while (tree)
	{
		tmp = tree->next;
		free(tree->str1);
		free(tree);
		tree = tmp;
	}
}

void	ft_freeshell(t_shell *shell)
{
	ft_freeenv(shell->env);
<<<<<<< HEAD
<<<<<<< HEAD
	ft_freeexp(shell->exp);
=======
>>>>>>> 49850c4 (Lexer Leaks removed)
=======
	ft_freeexp(shell->exp);
>>>>>>> bc19d77 (Day End)
	free(shell->line);
	free(shell);
}

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

<<<<<<< HEAD
void	ctrl_d(t_shell *shell)
{
	ft_freeshell(shell);
	ft_printf("exit\n");
	exit(0);
}

/* void	loop_shell(t_shell *shell)
{
	char	**cmd;

	while (true)
	{
		ft_comand_signal();

		shell->line = readline("minishell -> ");
<<<<<<< HEAD
		cmd = ft_split(shell->line, ' ');
		if (!shell->line)
		{
=======
		if (!shell->line || !ft_strcmp(shell->line, "exit"))
			ctrl_d(shell);
		else if (!ft_strlen(shell->line) || ft_chk_char(shell->line))
>>>>>>> 8fd3012 (12/10/23)
			free(shell->line);
		else
		{
			add_history(shell->line);
			start_cmd(shell);
			free(shell->line);
			ft_freetree(shell->tree);
		}
		if (is_builtin(cmd))
			exec_builtin(cmd, shell);
		//ft_printf("%s\n", shell->line);
		free(shell->line);
	}
} */
<<<<<<< HEAD
=======
void ctrl_d(t_shell *shell)
{
		ft_freeshell(shell);
		ft_printf("exit\n");
		exit(0);
}

// loop_shell() is a function that loops the shell and prints the prompt.
>>>>>>> 49850c4 (Lexer Leaks removed)
=======
>>>>>>> bc19d77 (Day End)

void	loop_shell(t_shell *shell)
{
	while (true)
	{
		ft_comand_signal();
		shell->line = readline("minishell -> ");
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> bc19d77 (Day End)
		if (!shell->line)
			ctrl_d(shell);
		else if (!ft_strlen(shell->line) || ft_chk_char(shell->line))
			free(shell->line);
		else
		{
			add_history(shell->line);
			start_cmd(shell);
			parse_execute(shell);
<<<<<<< HEAD
=======
		if (!shell->line || !ft_strcmp(shell->line, "exit"))
			ctrl_d(shell);
		else if (ft_chk_char(shell->line))
			free(shell->line);
		else
		{
			add_history(shell->line);
			start_cmd(shell);
>>>>>>> 49850c4 (Lexer Leaks removed)
=======
>>>>>>> bc19d77 (Day End)
			free(shell->line);
			ft_freetree(shell->tree);
		}
	}
	ft_freeshell(shell);
	exit(g_signal_exit);
}

void	print_start_minishell(void)
{
	char	ascii[2860];
	int		result;
	int		fd;
	ssize_t	read_bytes;

	fd = open("./.ascii", O_RDONLY);
<<<<<<< HEAD
	if (fd == -1) 
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
=======
	if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
>>>>>>> bc19d77 (Day End)
	result = read(fd, &ascii, 2860);
	read_bytes = write(1, ascii, result);
	if (read_bytes == -1) 
	{
<<<<<<< HEAD
		perror("write");
		close(fd);
		exit(EXIT_FAILURE);
	}
=======
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
>>>>>>> bc19d77 (Day End)
	close(fd);
}

void ft_print_list(t_shell *list)
{
<<<<<<< HEAD
<<<<<<< HEAD
	t_tree	*tmp;

	tmp = list->tree;
	while (tmp)
	{
		printf("%s - %i\n", tmp->str1, tmp->type);
		tmp = tmp->next;
	}
	free(tmp);
=======
=======
>>>>>>> bc19d77 (Day End)
	t_tree *tmp;
	
	tmp = list->tree;
	while(tmp)
	{
		printf("%s - %i\n",tmp->str1, tmp->type);
		tmp = tmp->next;
	}
	free(tmp);	
<<<<<<< HEAD
>>>>>>> 49850c4 (Lexer Leaks removed)
}

=======
}


>>>>>>> bc19d77 (Day End)
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