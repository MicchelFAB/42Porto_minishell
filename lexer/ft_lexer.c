/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:07 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/18 20:23:47 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

char	*rm_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i += skip_quotes(&s[i]);
		else if (s[i] == '\\')
		{
			s = ft_rmvchar(s, i);
			i += 2;
		}
		else if (ft_isspace(s[i]))
			s[i] = -1;
		i++;
	}
	return (s);
}

int	str_whitespace_only(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

t_tree	*ft_create_tree(int type, char *str)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(sizeof(t_tree));
	if (new_tree == NULL)
		return (NULL);
	new_tree->str1 = ft_strdup(str);
	new_tree->type = type;
	new_tree->next = NULL;
	free(str);
	return (new_tree);
}

t_tree	*ft_lexer(t_shell *line)
{
	t_tree	*list;

	if (line->line == NULL)
		return (NULL);
	line->line = ft_expand_env(line);
	line->line = rm_whitespace(line->line);
	ft_convert_especial(line);
	list = ft_split_lexer(line->line);
	if (list == NULL)
		return (NULL);
	return (list);
}

void	start_cmd(t_shell *shell)
{
	if (shell->line[0] != '\0')
	{
		shell->tree = ft_lexer(shell);
		if (shell->tree == NULL)
			g_signal_exit = 0;
	}
}

char	*ft_ignore_special(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			if (!ft_chk_char(line))
				i++;
			else
				line = ft_rmvchar(line, i);
		}
		else if (line[i] == '\'')
			i += skip_quotes(&line[i]);
		else if (line[i] == '\"' && line[i - 1] == '\\')
			line = ft_rmvchar(line, i++);
		i++;
	}
	return (line);
}

void	ft_convert_especial(t_shell *shell)
{
	if (ft_strchr(shell->line, '~') && !ft_chk_char(shell->line))
		shell->line = ft_str_replace(shell->line, "~", "$HOME");
	if (ft_strchr(shell->line, '\'') || ft_strchr(shell->line, '\"'))
		shell->line = ft_remove_quotes(shell->line);
	if (ft_strchr(shell->line, '\\'))
		shell->line = ft_ignore_special(shell->line);
}
