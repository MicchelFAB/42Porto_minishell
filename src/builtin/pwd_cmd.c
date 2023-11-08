/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:55:24 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/08 12:41:46 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
getcwd() — Get path name of the working directory
*/

void	pwd_cmd(char **cmd)
{
	char	pwd[256];

	if (cmd[1])
		print_error("pwd: options aren't supported", 1, "minishell");
	else if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
}
