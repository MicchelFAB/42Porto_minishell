/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:07 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/06 17:38:24 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

int	skip_quotes(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
	{
		i++;
		if (!s[i])
			return (0);
		ft_skip_escape(s, &i);
		i--;
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
	//int	flag;

	i = -1;
	//flag = 0;
	while (line[++i])
	{
		if (line[i] == ';' || line[i] == '&' || line[i] == '*' || line[i]
			== (line[i] == '|' && line[i + 1] && line[i + 1] == '|'))
		{
			if (check_quote_pair(line, i) == 0 && i && line[i - 1] != '\\')
			{
				ft_printf("minishell: no support for operator `%c'\n",
					line[i]);
				return (1);
			}
		}
	}
	return (0);
}

int	ft_verify_quote(char *s, int i)
{
	if (i == 1)
		i = 0;
	else if (skip_quotes(s) != 0 && i == 0)
		i = 1;
	return (i);
}
