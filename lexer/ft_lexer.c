/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:07 by mamaral-          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/10/12 22:27:48 by mamaral-         ###   ########.fr       */
=======
/*   Updated: 2023/10/03 18:40:33 by mamaral-         ###   ########.fr       */
>>>>>>> 49850c4 (Lexer Leaks removed)
=======
/*   Updated: 2023/10/09 18:31:39 by mamaral-         ###   ########.fr       */
>>>>>>> c9d4cc5 (09-10)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signal_exit;

char *ft_exit_nbr(char *str)
{
	char *nbr;
	nbr = ft_itoa(g_signal_exit);
	free(str);
	return (nbr);	
}

char *ft_change_str(char *s1, char *s2)
{
	free(s1);
	return (s2);
}

void	ft_putspecial(char *str, char *line, int *i, int *j)
{
	str[(*j)++] = ' ';
	str[(*j)++] = line[(*i)++];
	if (check_quote_pair(line, *i) == 0
		&& (line[*i] == '>' || line[*i] == '<' || line[*i] == '|'))
		str[(*j)++] = line[(*i)++];
	str[(*j)++] = ' ';
}

int	ft_elements(char *s, int i)
{
	if (i > 0 && s[i - 1] == '\\' && ft_strchr("><;|", s[i]))
		return (0);
	else if (ft_strchr("><;|", s[i]) && check_quote_pair(s, i) == 0)
		return (1);
	else
		return (0);
}

<<<<<<< HEAD
=======
/* char	*malloc_rd(char *s)
{
	char	*rest;
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (ft_elements(s, i))
			n++;
		i++;
	}
	rest = (char *)malloc(sizeof(char) * (i + 2 * n + 1));
	if (!rest)
		return (NULL);
	ft_bzero(rest, i + 2 * n + 1);
	return (rest);
} */

char	*ft_quote_data(char *str, t_shell *line, int *i, int *j)
{
	if (line->line[*i + 1] && line->line[*i + 1] == '\"')
		str[(*j)++] = (char)(line->line[(*i)++]);
	else if (line->line[*i + 1] && line->line[*i + 1] == '\'')
		(*i)++;
	else
	{
		str[*j] = check_next_char(line->line, *i);
			if (str[*j] == -2)
			{
				str = get_merged_str(line, str, j);
				while(!isspace(line->line[*i]) && line->line[*i] != '\0')
					(*i)++;
			}
	}
	return(str);
}

>>>>>>> c9d4cc5 (09-10)
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
<<<<<<< HEAD
<<<<<<< HEAD
	line->line = ft_expand_env(line);
=======
	// list = ft_create_tree(NULL_S, NULL);
	//line->line = ft_expand_env(line->line, line->env);
>>>>>>> 49850c4 (Lexer Leaks removed)
=======
	line->line = ft_expand_env(line);
>>>>>>> c9d4cc5 (09-10)
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
	}
}