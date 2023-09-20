/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:31 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/20 14:58:10 by mamaral-         ###   ########.fr       */
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
	t_env	*env;
	t_exp	*exp;
}				t_shell;

char 	*ft_rd_instr(char *instr);
void	ft_addenv_back(t_env **lst, t_env *new);
int 	start_cmd(t_shell *shell);
void	ft_addenv_back(t_env **lst, t_env *new);
void ft_freeenv(t_env *env);
t_env	*ft_envnew(char *key, char *value);
void ft_import_env(t_shell *shell, char **env);
int ft_printenv(t_env *shell);

#endif