/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:54 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/16 15:38:32 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_char(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str != c)
			i++;
		str++;
	}
	return (i);
}

char	*ft_char_rm(char *s1, char set)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_skip_char(s1, set) + 1));
	while (s1[i])
	{
		if (s1[i] != set)
			str[j++] = s1[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_remove_quotes(char *str)
{
	char	*stash;

	if (str[0] == '\'')
		stash = ft_char_rm(str, '\'');
	else if (str[0] == '\"')
		stash = ft_char_rm(str, '\"');
	else
		stash = ft_strdup(str);
	free(str);
	return (stash);
}

char	*ft_remove_escape(char *str)
{
	char	*stash;

	if (ft_strchr(str, '\\'))
	{
		stash = ft_char_rm(str, '\\');
		free(str);
		return (stash);
	}
	else
		return (str);
}

void	add_next(t_tree *new, t_tree *start)
{
	t_tree	*curr;

	curr = start;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

t_tree	*make_tree(char *str, int size)
{
	t_tree	*tree;
	char	*new_str;
	int		type;

	if (size == 0)
		return (NULL);
	new_str = ft_substr(str, 0, (size));
	if (new_str[0] == '|')
		type = PIPE;
	else if (new_str[0] == '<')
		type = REDIR;
	else if (new_str[0] == '>')
		type = REDIR;
	else
	{
		if (new_str[0] == '\'' || new_str[0] == '\"')
			new_str = ft_remove_quotes(new_str);
		else
			new_str = ft_remove_escape(new_str);
		type = WORD;
	}
	tree = ft_create_tree(type, new_str);
	return (tree);
}

t_tree	*ft_split_lexer(char *str)
{
	t_tree		*start;
	int			i;
	int			stash;

	i = 0;
	start = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == -1)
			i++;
		else
		{
			stash = i;
			while (str[i] != -1 && str[i] != '\0')
				i++;
			if (start == NULL)
				start = make_tree(&str[stash], i - stash);
			else
				add_next(make_tree(&str[stash], i - stash), start);
		}
	}
	return (start);
}
