/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:51:42 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/06 15:51:43 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	print_export(t_shell *shell)
{
	t_exp	*lst;

	lst = shell->exp;
	while (lst)
	{
		if (!lst->value)
			printf("declare -x %s\n", lst->key);
		else
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		lst = lst->next;
	}
	g_signal_exit = 0;
}

t_exp	*search_exp(char *key, t_shell *shell)
{
	t_exp	*search;

	search = shell->exp;
	while (search != NULL)
	{
		if (ft_strcmp(key, search->key) == 0)
			return (search);
		search = search->next;
	}
	return (NULL);
}

int	ft_set_exp(char *key, char *new_val, t_shell *shell)
{
	t_exp	*new_exp;
	t_exp	*search;

	search = search_exp(key, shell);
	if (search)
	{
		if (search->value != NULL)
			free(search->value);
		search->value = ft_strdup(new_val);
		return (0);
	}
	else
	{
		new_exp = ft_expnew(key, new_val);
		ft_addexp(&shell->exp, new_exp);
		return (0);
	}
	return (-1);
}

char	*ft_get_exp(char *key, t_shell *shell)
{
	t_exp	*search;

	search = shell->exp;
	while (search != NULL)
	{
		if (ft_strcmp(key, search->key) == 0)
			return (search->value);
		search = search->next;
	}
	return (NULL);
}
