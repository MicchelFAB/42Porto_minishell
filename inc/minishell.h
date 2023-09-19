/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:31 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/19 11:40:23 by mamaral-         ###   ########.fr       */
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


typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
}				t_env;

typedef struct s_exp
{
	char	*key;
	char	*value;
	struct s_exp *next;
}				t_exp;
typedef struct s_shell
{
	char	*line;
	int		signal;
	t_env	*env;
	t_exp	*exp;
}				t_shell;

char *ft_rd_instr(char *instr);
void	ft_addenv_back(t_env **lst, t_env *new);

#endif