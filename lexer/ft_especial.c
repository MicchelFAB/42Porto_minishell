/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_especial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:35:17 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/02 15:35:55 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

void	ft_skip_escape(char *s, int *i)
{
	while (s[*i] != '\"' && s[*i])
	{
		if (s[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	if (s[*i] == '\"')
		(*i)++;
}

void	ft_convert_especial(t_shell *shell)
{
	t_tree	*tmp;

	tmp = shell->tree;
	while (tmp)
	{
		if (ft_strchr(tmp->str1, '~') && !ft_chk_char(tmp->str1))
			tmp->str1 = ft_str_replace(tmp->str1, "~", "$HOME");
		if (ft_strchr(tmp->str1, '\'') || ft_strchr(tmp->str1, '\"'))
			tmp->str1 = ft_remove_quotes(tmp->str1);
		if (ft_strchr(tmp->str1, '\\'))
			tmp->str1 = ft_ignore_special(tmp->str1);
		if (tmp->type == REDIR && !ft_strcmp(tmp->str1, "<<"))
		{
			ft_heredoc_open(shell, tmp);
		}
		tmp = tmp->next;
	}
}

void	ft_heredoc_open(t_shell *shell, t_tree *tmp)
{
	char *name;
	
	name = ft_strdup(tmp->next->str1);
	ft_start_heredoc(shell, name);
	free(tmp->next->str1);
	free(name);
	tmp->next->str1 = ft_strdup(".heredoc");
	tmp->next->type = FILE;
}

void	ft_start_heredoc(t_shell *shell, char *tmp)
{
	int		pid;
	int		status;
	int 	fd;
	
	(void)shell;
	pid = fork();
	fd = 0;
	if (pid == 0)
		exit(ft_heredoc_child(tmp, shell));
	else
	{
		update_signal(pid, &status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			fd = open(".heredoc", O_WRONLY | O_TRUNC, 0644);
			close(fd);
			g_signal_exit = 130;
		}
	}
}
