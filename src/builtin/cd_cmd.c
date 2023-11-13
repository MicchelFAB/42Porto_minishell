/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:51:20 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/06 15:51:21 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

/*
 * getcwd Returns the current working directory
 * ft_set_path: take the OLDPWD and update to the current
 * ft_set_path: take the PWD and update to the newone
*/

void	update_pwd(t_shell *shell)
{
	char	new_pwd[256];

	if (getcwd(new_pwd, sizeof(new_pwd)))
	{
		ft_set_path("OLDPWD", ft_get_path("PWD", shell), shell);
		ft_set_path("PWD", new_pwd, shell);
	}
}

/*
 *take the new path, and update the path
*/

int	make_cd(char *path, t_shell *shell)
{
	g_signal_exit = chdir(path);
	if (g_signal_exit < 0)
		return (g_signal_exit);
	update_pwd(shell);
	return (g_signal_exit);
}

/*
 * get_path: search the HOME path
 * make_cd: take the new path and update
 * 
*/

int	go_old_path(char **path, t_shell *shell)
{
	*path = ft_get_path("OLDPWD", shell);
	if (!*path)
	{
		ft_putstr_fd("OLDPWD error\n", 2);
		g_signal_exit = 1;
		return (1);
	}
	printf("%s\n", ft_get_path("OLDPWD", shell));
	return (0);
}

void	cd_cmd(char **cmd, t_shell *shell)
{
	char	*path;

	path = cmd[0];
	if (cmd[0] && cmd[1])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		g_signal_exit = 1;
		return ;
	}
	if ((path == NULL || *path == '\0') || (*path == '-' && *(path + 1) == '-'
			&& *(path + 2) == '\0'))
		path = ft_get_path("HOME", shell);
	else if (*path == '-' && *(path + 1) == '\0')
	{
		if (go_old_path(&path, shell))
			return ;
	}
	if (make_cd(path, shell) < 0)
	{
		g_signal_exit = 1;
		perror("cd");
	}
}
