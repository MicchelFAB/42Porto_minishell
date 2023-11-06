/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:58:58 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/06 17:26:34 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	clean_all(t_shell *shell)
{
	if (shell->env)
		ft_freeenv(shell->env);
	if (shell->exp)
		ft_freeexp(shell->exp);
	if (shell->line)
		free(shell->line);
	if (shell->tree)
		ft_freetree(shell->tree);
	if (shell)
		free(shell);
	close_fd();
	rl_clear_history();
}

void	free_split(char **ptr)
{
	int		i;

	i = 0;
	while (ptr[i])
		i++;
	while (--i >= 0)
		free(ptr[i]);
	free(ptr);
}

void	close_fd(void)
{
	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
	dup2(STDERR_FILENO, 2);
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
