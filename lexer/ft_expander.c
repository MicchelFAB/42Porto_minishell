/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:28:36 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/17 09:38:20 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_env(t_shell *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line->line[i])
	{
		if (line->line[i] == '\"')
			j = ft_verify_quote(&line->line[i], j);
		if (line->line[i] == '\'' && j == 0)
			i += skip_quotes(&line->line[i]);
		if (line->line[i] == '$')
		{
			{
				line->line = get_merged_str(line, &i);
				if (line->line == NULL)
					break ;
			}
		}
		else
			i++;
	}
	line->line[i] = '\0';
	return (line->line);
}

int	ft_verify_quote(char *s, int i)
{
	if (i == 1)
		i = 0;
	else if (skip_quotes(s) != 0 && i == 0)
		i = 1;
	return (i);
}

void	*get_merged_str(t_shell *line, int *i)
{
	char	*key;
	char	*value;
	char	*str;
	char	*result;
	
	str = ft_strdup(&line->line[*i]);
	key = get_env_name(str + 1);
	free(str);
	str = ft_strjoin("$", key);
	value = get_env_to_str(key, line->env);
	*i += ft_strlen(value);
	result = ft_str_replace(line->line, str, value);
	if(*value)
		free(value);
	free(str);
	free(key);
	return(result);
}

char	*get_env_to_str(char *str, t_env *env)
{
	t_env *tmp;
	char *name;
	
	tmp = env;
	if (env == NULL)
		return (NULL);
	if (str[0] == '?' && str[1] == '\0')
		return (ft_exit_nbr(str));
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
		{
			name = ft_strdup(tmp->value);
			return(name);
		}
		tmp = tmp->next;
	}
	free(tmp);
	return ("");
}

char	*get_env_name(char *s)
{
	int		i;
	int		j;
	char	*name;

	j = 0;
	i = env_key_size(s);
	if (i == 0)
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (name == NULL)
		return (NULL);
	while (i > 0)
	{
		name[j] = s[j];
		j++;
		i--;
	}
	name[j] = '\0';
	// free(s);
	return (name);
}

int	env_key_size(char *s)
{
	int		i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (i + 1);
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			break ;
		i++;
	}
	return (i);
}

char * find_next_occurence(char *line)
{
	char * dolar_sign;
	
	while(1)
	{
		dolar_sign = ft_strchr(line, '$');
		
		if (!dolar_sign)
			return NULL;
		
		if (ft_isalpha(*(dolar_sign + 1)) && *(dolar_sign + 1) == '_')
			return dolar_sign;

		line = dolar_sign;
	}
}

int ft_strstr(char *str, char *to_find)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (i + j);
			j++;
		}
		i++;
	}
	return (0);
}
