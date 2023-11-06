/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:55:24 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/06 15:55:25 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
getcwd() — Get path name of the working directory
*/

void	pwd_cmd(void)
{
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
}
