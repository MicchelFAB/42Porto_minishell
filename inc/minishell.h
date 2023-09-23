/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:31 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/12 09:27:12 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	struct s_env	*next;
}				t_env;

typedef struct minishell
{
	t_env	*env;
	int		fd;
	char	*line;
	char	**command;
	int		signal;
}				t_shell;

/*------------main------------*/
int		main(int ac, char **av, char **env);
void	loop_shell(t_shell *shell);
t_shell	*init_shell(char **env);

/*------------builtin---------*/
void	pwd_cmd(void);
void	echo_cmd(char **cmd);
void	exec_builtin(char **cmd);
int		is_builtin(char **cmd);

#endif