/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:51:03 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/13 18:20:16 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_path(char *key, t_shell *shell)
{
	t_env	*search;

	search = shell->env;
	while (search != NULL)
	{
		if (!ft_strcmp(key, search->key))
			return (search);
		search = search->next;
	}
	return (NULL);
}

int	ft_set_path(char *key, char *new_val, t_shell *shell)
{
	t_env	*newenv;
	t_env	*search;

	search = search_path(key, shell);
	if (search)
	{
		free(search->value);
		search->value = ft_strdup(new_val);
		return (0);
	}
	else
	{
		newenv = ft_envnew(key, new_val);
		ft_addenv_back(&shell->env, newenv);
		return (0);
	}
	return (-1);
}

char	*ft_get_path(char *key, t_shell *shell)
{
	t_env	*path;

	path = shell->env;
	while (path != NULL)
	{
		if (!ft_strcmp(key, path->key))
			return (path->value);
		path = path->next;
	}
	return (NULL);
}

int	contains_pipe(t_shell *shell)
{
	t_tree	*tmp;

	tmp = shell->tree;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_unset(char **cmd)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (ft_isalnum(cmd[i][j]) || cmd[i][j] == '_')
				j++;
			else
			{
				ft_putstr_fd("minishell: unset: ", 2);
				print_error("not a valid identifier", 1, cmd[i]);
				k = 1;
				j++;
			}
		}
		i++;
	}
	return (k);
}
