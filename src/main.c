/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:40:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/09 11:05:04 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_exit;

int	is_dollar_sign(char *s, int *i)
{
	if (s[0] == '$' && s[1] != '\0')
		return (1);
	else if (s[0] == '\\' && s[1] == '$')
		*i += 1;
	return (0);
}

int	ft_chk_line(char *line)
{
	int	size;

	size = ft_strlen(line);
	if (check_special(line) || str_whitespace_only(line))
		return (1);
	if (check_quote_pair(line, size))
	{
		print_error(" syntax error, all quotes need to be closed!", 2,
			"minishell");
		return (1);
	}
	return (0);
}

void	loop_shell(t_shell *shell)
{
	while (true)
	{
		ft_comand_signal();
		shell->line = readline("minishell -> ");
		if (!shell->line)
			ctrl_d(shell);
		else if (!ft_strlen(shell->line) || ft_chk_line(shell->line))
		{
			add_history(shell->line);
			free(shell->line);
		}
		else
		{
			add_history(shell->line);
			if (ft_lexer(shell))
			{
				parse_execute(shell);
				wait_child_proc(shell);
			}
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
