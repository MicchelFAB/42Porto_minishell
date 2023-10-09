/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:31 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/09 18:37:58 by mamaral-         ###   ########.fr       */
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

# define	NULL_S		0
# define	WORD		1
# define	REDIR		2
# define	PIPE		3
# define	CMD			4
# define	SIMP_CMD	5
# define	AND			6
# define	OR			7

typedef struct s_lexer
{
	char	*token;
	char	*args;
	struct s_lexer *next;
} 				t_lexer;

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
typedef struct s_tree
{
	int 			type;
	char			*str1;
	struct s_tree *next;
}	t_tree;
typedef struct s_shell
{
	char	*line;
	t_env	*env;
	t_exp	*exp;
	t_tree	*tree;
	int		t_count;
}				t_shell;

char 	*ft_rd_instr(char *instr);
void	ft_addenv_back(t_env **lst, t_env *new);
void 	start_cmd(t_shell *shell);
void	ft_addenv_back(t_env **lst, t_env *new);
void ft_freeenv(t_env *env);
t_env	*ft_envnew(char *key, char *value);
void ft_import_env(t_shell *shell, char **env);
int ft_printenv(t_env *shell);
int	check_quote_pair(char *s, int double_flag);
int	skip_quotes(char *s);
int ft_chk_char(char *line);
t_tree	*ft_create_tree(int type, char *str);
int str_whitespace_only(char *str);
t_tree	*ft_split_lexer(char *str);
void ft_print_list(t_shell *list);
void ft_freetree(t_tree *tree);

/*  EXPANDER */

char	*ft_expand_env(t_shell *line);
char	check_next_char(char *str, int i);
char	*get_merged_str(t_shell *line, char *str, int *i);
char	*get_env_to_str(char *str, t_env *env);
char	*ft_join_str_env(char *s, char *env);
char	*get_env_name(char *s);
int		env_key_size(char *s);
int		ft_elements(char *str, int i);
char 	*ft_exit_nbr(char *str);
char	*ft_quote_data(char *str, t_shell *line, int *i, int *j);
char	*ft_strjoin_null(char *s1, char *s2);
void	ft_putspecial(char *str, char *line, int *i, int *j);

#endif