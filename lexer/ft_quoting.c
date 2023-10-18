/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:07 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/18 19:37:43 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

int	ft_skip_escape(char *s, int i)
{
	while (s[i] != '\"' && s[i])
	{
		if (s[i] == '\\')
			i += 2;
		i++;
	}
	return (i);
}

int	skip_quotes(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
	{
		i++;
		if (!s[i])
			return (0);
		i = ft_skip_escape(s, i);
	}
	else if (s[i] == '\'')
	{
		i++;
		if (!s[i])
			return (0);
		while (s[i] != '\'' && s[i])
			i++;
	}
	if (s[i] == '\0')
		return (0);
	return (i);
}

void	find_qpair(int *result, int *flag, int insert)
{
	if (!(*flag))
		(*result) = insert;
	(*flag) = 0;
}

int	check_quote_pair(char *s, int size)
{
	int	i;
	int	result;
	int	flag;

	i = 0;
	result = 0;
	flag = 0;
	while (s[i] && i != size)
	{
		if (!flag && s[i] == '\\' && result != 2)
			flag = 1;
		else if (result == 0 && s[i] == '\"')
			find_qpair(&result, &flag, 1);
		else if (result == 0 && s[i] == '\'')
			find_qpair(&result, &flag, 2);
		else if (result == 1 && s[i] == '\"')
			find_qpair(&result, &flag, 0);
		else if (result == 2 && s[i] == '\'')
			find_qpair(&result, &flag, 0);
		else if (flag)
			flag = 0;
		i++;
	}
	return (result);
}

int	check_special(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '&' || line[i] == '*' || line[i] == 
			(line[i] == '|' && line[i + 1] && line[i + 1] == '|'))
		{
			if (check_quote_pair(line, i) == 0)
			{
				if (i && line[i - 1] != '\\')
					return (1);
			}
		}
		if (line[i] == '<' || line[i] == '>')
			flag = 1;
		i++;
	}
	if (i != 1 && line[i - 1] == '|' && !flag)
		return (1);
	return (0);
}
