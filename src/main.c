/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/19 10:52:44 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_freeenv(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*ft_envnew(char *key, char *value)
{
	t_env *new_env;
	
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		return (NULL);
	}
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	return (new_env);
	}


void ft_import_env(t_shell *shell, char **env)
{
	t_env	*new;
	int i;
	size_t size;
	char *key;
	char *value;

	i = 0;
	shell->env = NULL;
	while(env[i])
	{
		if(strchr(env[i], '='))
		{
			size = ft_strlen_at(env[i], '=');
			key = malloc(size + 1);
			ft_memcpy(key, env[i], size);
			key[size] = '\0';
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
			new = ft_envnew(key, value);
			new->next = NULL;
			ft_addenv_back(&shell->env, new);
			free(key);
			free(value);
		}
		i++;
	}
}

void ft_ctrlc(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

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
	shell->signal = 0;
	ft_import_env(shell, env);
	// shell->exp = ft_import_exp(&shell, env);
}

// loop_shell() is a function that loops the shell and prints the prompt.

void	loop_shell(t_shell *shell)
{
	// char	*line;

	while (true)
	{
		ft_comand_signal();
		shell->line = readline("minishell -> "); 
		if (!shell->line || !ft_strcmp(shell->line, "exit"))
		{
			free(shell->line);
			ft_freeenv(shell->env);
			ft_printf("exit\n");
			exit(0);
		}
		ft_printf("%s\n", shell->line);
		add_history(shell->line);
		free(shell->line);
	}
}

int	main(int ac, char **av, char **env) // ac = argument count, av = argument vector, env = environment
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell(&shell, env);
	loop_shell(&shell);
	return (0);
}
