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

/*------------main------------*/
int		main(int ac, char **av, char **env);
void	loop_shell(t_shell *shell);
void 	init_shell(t_shell *shell, char **env);

/*------------utils-----------*/
char 	*ft_rd_instr(char *instr);
void	print_error(char *msg, int error);
long long int	ft_atol(const char *nptr);

/*-----------clear------------*/
void	clean_all(t_shell *shell);
void	free_split(char **ptr);

/*------------ft_env----------*/
void	ft_addenv_back(t_env **lst, t_env *new);
int 	start_cmdenv(t_shell *shell);
void 	ft_freeenv(t_env *env);
t_env	*ft_envnew(char *key, char *value);
void 	ft_import_env(t_shell *shell, char **env);

/*-----------ft_env_utils------*/
int		ft_set_env(char *key, char *new_val, t_shell *shell);
t_env	*search_env(char *key, t_shell *shell);

/*-----------ft_exp------------*/
void	ft_import_exp(char **env, t_shell *shell);
void 	ft_freeexp(t_exp *exp);
t_exp	*ft_expnew(void *key, void *value);
void	ft_addexp(t_exp **lst, t_exp *new);
void	print_export(t_shell *shell);
char	*ft_get_exp(char *key, t_shell *shell);
int		ft_set_exp(char *key, char *new_val, t_shell *shell);

/*------------builtin---------*/
void	exit_cmd(char **cmd, t_shell *shell);
void	ft_exit_two_args(char **cmd, t_shell *shell);
int		ft_is_all_digit(char *num);
int		ft_is_number(char *num);

void	pwd_cmd(void);

void	cd_cmd(char **cmd, t_shell *shell);

void	echo_cmd(char **cmd);

void	export_cmd(char **cmd, t_shell *shell);

void	exec_builtin(char **cmd, t_shell *shell);
int		is_builtin(char **cmd);

/*-----------builtin_utils-----*/
char	*ft_get_path(char *key, t_shell *shell);
int		ft_set_path(char *key, char *new_val, t_shell *shell);
t_env	*search_path(char *key, t_shell *shell);
int		go_old_path(char **path, t_shell *shell);

#endif