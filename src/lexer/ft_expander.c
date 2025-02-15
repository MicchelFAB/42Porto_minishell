/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:28:36 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/10 11:47:57 by mamaral-         ###   ########.fr       */
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
		if (is_dollar_sign(&line->line[i], &i))
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

void	*get_merged_str(t_shell *line, int *i)
{
	char	*key;
	char	*value;
	char	*str;
	char	*result;

	if (line->line[*i] == '$' && ((line->line[*i + 1] == ' ') \
		|| line->line[*i + 1] == '\"' || line->line[*i + 1] == '\''))
	{
		(*i)++;
		return (line->line);
	}
	str = ft_strdup(&line->line[*i]);
	key = get_env_name(str + 1);
	free(str);
	str = ft_strjoin("$", key);
	value = get_env_to_str(key, line->env);
	result = ft_str_replace(line->line, str, value, *i);
	*i += ft_strlen(value);
	if (*value)
		free(value);
	free(str);
	free(key);
	return (result);
}

char	*get_env_to_str(char *str, t_env *env)
{
	t_env	*tmp;
	char	*name;

	tmp = env;
	if (env == NULL)
		return ("");
	if (str[0] == '?' && str[1] == '\0')
		return (ft_exit_nbr());
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
		{
			name = ft_strdup(tmp->value);
			return (name);
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
