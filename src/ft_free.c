/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:41:40 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/17 09:43:17 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freetree(t_tree *tree)
{
	t_tree	*tmp;

	while (tree)
	{
		tmp = tree->next;
		free(tree->str1);
		free(tree);
		tree = tmp;
	}
}

void	ft_freeshell(t_shell *shell)
{
	ft_freeenv(shell->env);
	ft_freeexp(shell->exp);
	free(shell->line);
	free(shell);
	rl_clear_history();
}

void	ft_freeexp(t_exp *exp)
{
	t_exp	*tmp;

	while (exp)
	{
		tmp = exp->next;
		free(exp->key);
		free(exp->value);
		free(exp);
		exp = tmp;
	}
}

void	ft_freeenv(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
