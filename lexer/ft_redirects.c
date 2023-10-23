/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:01:01 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/19 18:31:45 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*malloc_rd(char *s)
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
}

char *ft_put_redir(t_shell *line)
{
	char *tmp;
	int i;
	int j;

	j = 0;
	i = 0;
	tmp = malloc_rd(line->line);
	while (tmp && line->line[i])
	{
		if (check_quote_pair(line->line, i) == 0 && ft_elements(line->line, i))
			ft_putspecial(tmp, line->line, &i, &j);
		else
			tmp[j++] = line->line[i++];
	}
	tmp[j] = 0;
	free(line->line);
	return (tmp);
}

// //funcao para redirecionamento de input
// int ft_redirect_in(char *str, int flags)
// int input_file = open("input.txt", flags);

// //funcao para redirecionamento de output
// int output_file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

