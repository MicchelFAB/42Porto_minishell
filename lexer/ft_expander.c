/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:28:36 by mamaral-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/12 21:59:33 by mamaral-         ###   ########.fr       */
=======
/*   Updated: 2023/10/09 18:48:43 by mamaral-         ###   ########.fr       */
>>>>>>> c9d4cc5 (09-10)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_env(t_shell *line)
{
<<<<<<< HEAD
=======
	char *str;
>>>>>>> c9d4cc5 (09-10)
	int	i;
	int	j;

	i = 0;
	j = 0;
<<<<<<< HEAD
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
	return(line->line);
}

int	ft_verify_quote(char *s, int i)
{
	if (i == 1)
		i = 0;
	else if (skip_quotes(s) != 0 && i == 0)
		i = 1;
	return (i);
=======
	printf("teste\n");
	str = ft_strdup(line->line);
	while (str && line->line[i])
	{
		if (check_quote_pair(line->line, i) != 2 && line->line[i] == '$' && i && line->line[i - 1] != '\\')
			str = ft_quote_data(str, line, &i, &j);
		else if ((check_quote_pair(line->line, i) == 0 && ft_elements(line->line, i)))
			ft_putspecial(str, line->line, &i, &j);
		else
			str[j++] = line->line[i++];
	}
	free(line->line);
	str[j] = '\0';
	return(str);
>>>>>>> c9d4cc5 (09-10)
}

char	check_next_char(char *str, int i)
{
	if (str[i + 1] == '?')
		return(-2);
	else if (!(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		return(-3);
	else
		return(-2);
}

<<<<<<< HEAD
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
=======
char	*get_merged_str(t_shell *line, char *str, int *i)
{
	char	*env;

	env = get_env_to_str(get_env_name(&line->line[*i + 1]), line->env);
	*i += ft_strlen(env);
	str = ft_join_str_env(str, env);
	// free(env);
	return (str);
>>>>>>> c9d4cc5 (09-10)
}

char	*get_env_to_str(char *str, t_env *env)
{
	t_env *tmp;
<<<<<<< HEAD
	char *name;
=======
>>>>>>> c9d4cc5 (09-10)
	
	tmp = env;
	if (env == NULL)
		return (NULL);
	if (str[0] == '?' && str[1] == '\0')
		return (ft_exit_nbr(str));
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
		{
<<<<<<< HEAD
			name = ft_strdup(tmp->value);
			return(name);
		}
		tmp = tmp->next;
	}
=======
			free(str);
			return(ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	free(str);
>>>>>>> c9d4cc5 (09-10)
	free(tmp);
	return ("");
}

<<<<<<< HEAD
=======
char	*ft_join_str_env(char *s, char *env)
{
	int		i;
	char	*start;
	char	*end;
	char	*str1;
	char	*str2;

	i = 0;
	while (s[i] != -2)
		i++;
	if (i != 0)
		start = ft_substr(s, 0, i);
	else
		start = NULL;
	if (s[env_key_size(&s[i + 1]) + i + 1])
		end = ft_strdup(&s[env_key_size(&s[i + 1]) + i + 1]);
	else
		end = NULL;
	str1 = ft_strjoin_null(start, env);
	str2 = ft_strjoin_null(str1, end);
	// free(s);
	return (str2);
}

>>>>>>> c9d4cc5 (09-10)
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
<<<<<<< HEAD
	// free(s);
=======
>>>>>>> c9d4cc5 (09-10)
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
<<<<<<< HEAD

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
=======
>>>>>>> c9d4cc5 (09-10)
