/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:07 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/02 11:22:45 by mamaral-         ###   ########.fr       */
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
		else if (s[i] == '\\' && s[i + 1])
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

void	ft_lexer(t_shell *line)
{
	t_tree	*list;

	if (line->line == NULL)
		line->tree = NULL;
	if (ft_strchr(line->line, '~') && !ft_chk_char(line->line))
		line->line = ft_str_replace(line->line, "~", "$HOME");
	line->line = ft_put_redir(line);
	line->line = ft_expand_env(line);
	line->line = rm_whitespace(line->line);
	list = ft_split_lexer(line->line);
	if (list == NULL)
		line->tree = NULL;
	line->tree = list;
	ft_convert_especial(line);
}

char	*ft_ignore_special(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1])
		{
			if (!ft_chk_char(line) && !(line[i + 1] == '$'
					|| line[i + 1] == '\\'))
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
