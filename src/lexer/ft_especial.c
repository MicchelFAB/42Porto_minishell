/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_especial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:35:17 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:46 by bmonteir         ###   ########.fr       */
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

int	ft_check_pipe(t_shell *shell)
{
	t_tree	*tmp;

	if (!shell->tree)
		return(0);
	tmp = shell->tree;
	if (tmp->type == PIPE)
	{
		print_error("syntax error near unexpected token `|'", 2, "minishell:");
		//clean_all(shell);
		return(g_signal_exit);
	}
	while (tmp)
	{
		if (tmp->type == PIPE && (!tmp->next || tmp->next->type == PIPE
			|| !ft_strcmp(tmp->str1, "||")))
		{
			print_error("syntax error near unexpected token `|'", 2,
				"minishell:");
			//clean_all(shell);
			return(g_signal_exit);
		}
		
		tmp = tmp->next;
	}
	return(0);
}

int	ft_convert_especial(t_shell *shell)
{
	t_tree	*tmp;

	tmp = shell->tree;
	while (tmp)
	{
		if (ft_strchr(tmp->str1, '\'') || ft_strchr(tmp->str1, '\"'))
			tmp->str1 = ft_remove_quotes(tmp->str1);
		if (ft_strchr(tmp->str1, '\\'))
			tmp->str1 = ft_ignore_special(tmp->str1);
		if (tmp->type == REDIR && !ft_strcmp(tmp->str1, "<<"))
		{
			if (tmp->next->type != WORD)
			{
				print_error("syntax error near token `<<'", 2, "minishel");
			}
				return (1);
			ft_heredoc_open(shell, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_heredoc_open(t_shell *shell, t_tree *tmp)
{
	char	*name;

	if (!tmp->next)
		return ;
	name = ft_strdup(tmp->next->str1);
	ft_start_heredoc(shell, name);
	free(tmp->next->str1);
	free(name);
	tmp->next->str1 = ft_strdup(".heredoc");
	tmp->next->type = FILE;
}

int	ft_check_tilde(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '~')
		{
			if ((line [i - 1] && line [i - 1] == ' ') && \
		((line [i + 1] == ' ' || line [i + 1] == '/') || line[i + 1] == '\0'))
				return (1);
		}
		i++;
	}
	return (0);
}
