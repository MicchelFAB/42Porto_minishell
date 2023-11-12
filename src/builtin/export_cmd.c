/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:55:20 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/06 15:55:21 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

/*  * recebe key que é o que está entre o export e o '='
 * cmd que é o que está depois do '='
 * type */

int	valid_key(char *key, char *cmd, char *type)
{
	int		i;

	i = 0;
	if (!(ft_isalpha(cmd[i]) || cmd[i] == '_'))
	{
		printf("minishell: %s: %s:", type, cmd);
		ft_putstr_fd(" not a valid identifier\n", 2);
		g_signal_exit = 1;
		return (0);
	}
	i++;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
		{
			printf("minishell: %s: %s:", type, key);
			ft_putstr_fd(" not a valid identifier\n", 2);
			g_signal_exit = 1;
			return (0);
		}
		i++;
	}
	g_signal_exit = 0;
	return (1);
}

void	make_export(char *cmd, t_shell *shell)
{
	char	*key;
	char	*value;
	int		len;

	len = 0;
	while (cmd[len] != '\0' && cmd[len] != '=')
		len++;
	key = ft_substr(cmd, 0, len);
	if (!valid_key(key, cmd, "export"))
	{
		free(key);
		return ;
	}
	if (cmd[len] != '=')
	{
		ft_set_exp(key, NULL, shell);
		free(key);
		return ;
	}
	value = ft_strdup(cmd + len + 1);
	ft_set_env(key, value, shell);
	ft_set_exp(key, value, shell);
	free(value);
	free(key);
}

void	export_cmd(char **cmd, t_shell *shell)
{
	int		i;

	i = -1;
	if (contains_pipe(shell))
		return ;
	while (cmd[++i])
	{
		make_export(cmd[i], shell);
	}
}
