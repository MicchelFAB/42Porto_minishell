/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:54 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/19 17:55:22 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_loop_remove(char *s, char c, int i)
{
	while (s[i])
	{
		if (s[i] == c)
		{
			s = ft_rmvchar(s, i);
			while (s[i] && s[i] != c)
				i = ft_skip_escape(s, i);
			s = ft_rmvchar(s, i);
		}
		else
			i++;
	}
	return (s);
}

char	*ft_remove_quotes(char *str)
{
	char	*stash;
	int		i;

	i = 0;
	stash = ft_strdup(str);
	while (stash[i] && !(stash[i] == '\'' || stash[i] == '\"'))
		i++;
	if (stash[i] == '\'')
	{
		stash = ft_loop_remove(stash, '\'', i);
	}
	else if (stash[i] == '\"')
	{
		stash = ft_loop_remove(stash, '\"', i);
	}
	free(str);
	return (stash);
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
		type = WORD;
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
				start 	= make_tree(&str[stash], i - stash);
			else
				add_next(make_tree(&str[stash], i - stash), start);
		}
	}
	return (start);
}
