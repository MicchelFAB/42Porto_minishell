/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:48:20 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/26 15:43:33 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

void	ft_addenv_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst == NULL || ft_strcmp((*lst)->key, new->key) >= 0)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		new->next = last->next;
		last->next = new;
	}
}

t_env	*ft_envnew(char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		return (0);
	}
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	return (new_env);
}

void	ft_import_env(t_shell *shell, char **env)
{
	t_env	*new;
	int		i;
	int		size;
	char	*key;
	char	*value;

	i = -1;
	shell->env = NULL;
	while (env[++i])
	{
		if (strchr(env[i], '='))
		{
			size = ft_strlen_at(env[i], '=');
			key = malloc(size + 1);
			ft_memcpy(key, env[i], size);
			key[size] = '\0';
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
			new = ft_envnew(key, value);
			new->next = NULL;
			ft_addenv_back(&shell->env, new);
			free(key);
			free(value);
		}
	}
}
