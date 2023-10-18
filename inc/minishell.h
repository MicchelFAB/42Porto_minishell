/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:31 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/18 19:54:53 by mamaral-         ###   ########.fr       */
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
# include <sys/wait.h>

# define NULL_S		0
# define WORD		1
# define REDIR		2
# define PIPE		3
# define CMD		4
# define SIMP_CMD	5
# define AND		6
# define OR			7

# define IN		0
# define OUT	1

typedef struct s_lexer
{
	char			*token;
	char			*args;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_exp	*next;
}					t_exp;

typedef struct s_tree
{
	int				type;
	char			*str1;
	struct s_tree	*next;
}					t_tree;

typedef struct s_shell
{
	char	*line;
	t_env	*env;
	t_exp	*exp;
	t_tree	*tree;
	int		t_count;
}			t_shell;

/*------------main------------*/
// int				main(int ac, char **av, char **env);
void			loop_shell(t_shell *shell);
t_shell			*init_shell(char **env);

/*------------utils-----------*/
void			print_error(char *msg, int error);
int				check_quote_pair(char *s, int double_flag);
char			check_next_char(char *str, int i);
void			print_start_minishell(void);
char			*ft_exit_nbr(char *str);

/*-----------clear------------*/
void			clean_all(t_shell *shell);
void			free_split(char **ptr);

/*-----------lexer------------*/
void			start_cmd(t_shell *shell);
t_tree			*ft_lexer(t_shell *line);
t_tree			*ft_create_tree(int type, char *str);
int				str_whitespace_only(char *str);
int				ft_chk_char(char *line);
int				check_quote_pair(char *s, int size);
int				skip_quotes(char *s);
int				check_special(char *line);
t_tree			*ft_split_lexer(char *str);
t_tree			*make_tree(char *str, int size);
void			ft_convert_especial(t_shell *shell);

/*------------ft_env----------*/
void			ft_addenv_back(t_env **lst, t_env *new);
t_env			*ft_envnew(char *key, char *value);
void			ft_import_env(t_shell *shell, char **env);
int				ft_printenv(t_env *shell);
void			ft_print_list(t_shell *list);

/*------------ft_expander----------*/
char			*ft_expand_env(t_shell *line);
void			*get_merged_str(t_shell *line, int *i);
char			*get_env_to_str(char *str, t_env *env);
char			*ft_join_str_env(char *s, char *env);
char			*get_env_name(char *s);
int				env_key_size(char *s);
int				ft_verify_quote(char *s, int i);

/*-----------ft_env_utils------*/
int				ft_set_env(char *key, char *new_val, t_shell *shell);
t_env			*search_env(char *key, t_shell *shell);
void			print_cmdenv(t_shell *shell);

/*-----------ft_exp------------*/
void			ft_import_exp(char **env, t_shell *shell);
t_exp			*ft_expnew(void *key, void *value);
void			ft_addexp(t_exp **lst, t_exp *new);
void			print_export(t_shell *shell);
char			*ft_get_exp(char *key, t_shell *shell);
int				ft_set_exp(char *key, char *new_val, t_shell *shell);

/*-----------ft_free-----------*/
void			ft_freeexp(t_exp *exp);
void			ft_freeenv(t_env *env);
void			ft_freetree(t_tree *tree);
void			ft_freeshell(t_shell *shell);

/*------------builtin---------*/
void			exit_cmd(char **cmd, t_shell *shell);
void			ft_exit_two_args(char **cmd, t_shell *shell);
int				ft_is_all_digit(char *num);
int				ft_is_number(char *num);

void			pwd_cmd(void);

void			cd_cmd(char **cmd, t_shell *shell);

void			echo_cmd(char **cmd);

void			export_cmd(char **cmd, t_shell *shell);

void			exec_builtin(char **cmd, t_shell *shell);
int				is_builtin(char **cmd);

void			unset_cmd(char **cmd, t_shell *shell);
void			unset_exp(char *key, t_shell *shell);
void			ft_exp_del(t_exp *exp);
void			unset_env(char *key, t_shell *shell);
void			ft_env_del(t_env *env);

/*-----------builtin_utils-----*/
char			*ft_get_path(char *key, t_shell *shell);
int				ft_set_path(char *key, char *new_val, t_shell *shell);
t_env			*search_path(char *key, t_shell *shell);
int				go_old_path(char **path, t_shell *shell);

/*-----------Parse-------------*/
void			parse_execute(t_shell *shell);
void			parse_pipe(t_tree *tree, int *std_in, t_shell *shell);
char			**create_cmds(t_tree *tree, t_tree *tmp);
void			execute(char **cmd, int *fd, int *std_in, t_shell *shell);
void			exec_cmd(char **cmd, int *fd, int *std_in, t_shell *shell);


char			*ft_remove_quotes(char *str);
int				check_special(char *line);
int				ft_skip_escape(char *s, int i);

#endif
