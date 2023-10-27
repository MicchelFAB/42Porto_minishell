/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_especial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:35:17 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/26 15:35:47 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_convert_especial(t_tree *tree)
{
	t_tree	*tmp;

	tmp = tree;
	while (tree)
	{
		if (ft_strchr(tree->str1, '~') && !ft_chk_char(tree->str1))
			tree->str1 = ft_str_replace(tree->str1, "~", "$HOME");
		if (ft_strchr(tree->str1, '\'') || ft_strchr(tree->str1, '\"'))
			tree->str1 = ft_remove_quotes(tree->str1);
		if (ft_strchr(tree->str1, '\\'))
			tree->str1 = ft_ignore_special(tree->str1);
		tree = tree->next;
	}
	tree = tmp;
}
