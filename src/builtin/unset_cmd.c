/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:55:28 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/13 18:17:51 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	ft_env_del(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

void	unset_env(char *key, t_shell *shell)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = shell->env;
	prev = NULL;
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		shell->env = tmp->next;
		ft_env_del(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	ft_env_del(tmp);
}

void	ft_exp_del(t_exp *exp)
{
	if (!exp)
		return ;
	free(exp->key);
	free(exp->value);
	free(exp);
}

void	unset_exp(char *key, t_shell *shell)
{
	t_exp	*tmp;
	t_exp	*prev;

	tmp = shell->exp;
	prev = NULL;
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		shell->exp = tmp->next;
		ft_exp_del(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	ft_exp_del(tmp);
}

void	unset_cmd(char **cmd, t_shell *shell)
{
	char	*key;
	int		i;
	int		j;
	int		k;

	if (contains_pipe(shell))
		return ;
	i = 0;
	k = 0;
	k = check_unset(cmd);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] != 0)
			j++;
		key = ft_substr(cmd[i], 0, j);
		unset_exp(key, shell);
		unset_env(key, shell);
		free(key);
		i++;
	}
	g_signal_exit = k;
}
