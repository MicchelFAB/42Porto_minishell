/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:07 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/17 10:00:36 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

char	*ft_exit_nbr(char *str)
{
	char	*nbr;

	nbr = ft_itoa(g_signal_exit);
	free(str);
	return (nbr);
}

char	*ft_change_str(char *s1, char *s2)
{
	free(s1);
	return (s2);
}

int	skip_quotes(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
	{
		i++;
		if (s[i] == '\0')
			return (0);
		while (s[i] != '\"' && s[i] != '\0')
			i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		if (s[i] == '\0')
			return (0);
		while (s[i] != '\'' && s[i] != '\0')
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
		if (line[i] == ';' || line[i] == '&' || line[i] == '*' || line[i] == '\\'
			|| (line[i] == '|' && line[i + 1] && line[i + 1] == '|'))
		{
			if (check_quote_pair(line, i) == 0)
			{
				if (!(line[i] == '\\' && line[i + 1]))
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

int ft_chk_char(char *line)
{
	int size;

	size = ft_strlen(line);
	if (check_quote_pair(line, size) || check_special(line)
			|| str_whitespace_only(line))
		return (1);
	return(0);
}

void	rm_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i += skip_quotes(&s[i]);
		}
		else if (ft_isspace(s[i]))
			s[i] = -1;
		if (s[i] != '\0')
			i++;
	}
}

int str_whitespace_only(char *str)
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
	t_tree *list;
	
	if (line->line == NULL)
		return (NULL);
	line->line = ft_expand_env(line);
	// list = ft_create_tree(NULL_S, NULL);
	//line->line = ft_expand_env(line->line, line->env);
	rm_whitespace(line->line);
	list = ft_split_lexer(line->line);
	if(list == NULL)
		return (NULL);
	return (list);
}


void ft_print_list(t_shell *list)
{
	while(list->tree)
	{
		printf("%s - %i\n",list->tree->str1, list->tree->type);
		free(list->tree->str1);
		list->tree = list->tree->next;
	}
	free(list->tree);
}

void start_cmd(t_shell *shell)
{
	
	if (shell->line[0] != '\0')
	{
		shell->tree = ft_lexer(shell);
		if (shell->tree == NULL)
			g_signal_exit = 0;
/* 		else
			ft_print_list(shell); */
	}
}
