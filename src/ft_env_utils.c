/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 23:43:06 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/17 10:01:14 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

t_env	*search_env(char *key, t_shell *shell)
{
	t_env	*search;

	search = shell->env;
	while (search != NULL)
	{
		if (ft_strcmp(key, search->key) == 0)
			return (search);
		search = search->next;
	}
	return (NULL);
}

int	ft_set_env(char *key, char *new_val, t_shell *shell)
{
	t_env	*new_env;
	t_env	*search;

	search = search_env(key, shell);
	if (search)
	{
		free(search->value);
		search->value = ft_strdup(new_val);
		return (0);
	}
	else
	{
		new_env = ft_envnew(key, new_val);
		ft_addenv_back(&shell->env, new_env);
		return (0);
	}
	return (-1);
}

void	print_cmdenv(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_signal_exit = 0;
}

void	ft_print_list(t_shell *list)
{
	t_tree	*tmp;

	tmp = list->tree;
	while (tmp)
	{
		printf("%s - %i\n", tmp->str1, tmp->type);
		tmp = tmp->next;
	}
	free(tmp);
}
