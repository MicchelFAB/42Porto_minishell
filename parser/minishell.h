#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>


int		main(int ac, char **av, char **envp);
int		get_next_line(char **line);
void	error(void);
void	usage(void);
int		open_file(char *av, int i);
char	*find_path(char *cmd, char **envp);
void	execute(char *av, char **envp);
void	child_proc(char *av, char **envp);
void	here_doc(char *limiter, int ac);


size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *larger, const char *small, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);


#endif