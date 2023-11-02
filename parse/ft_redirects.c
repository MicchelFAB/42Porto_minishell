#include "minishell.h"

extern int	g_signal_exit;

static int	ft_heredoc_loop2(char *s1)
{
	int		tmp;

	tmp = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tmp < 0)
		return (1);
	ft_putendl_fd(s1, tmp);
	close(tmp);
	free(s1);
	return (0);
}

static int	ft_heredoc_loop(char *name)
{
	char	*prompt;
	char	str[1000000];
	int		i;

	i = 0;
	ft_memset(str, 0, 1000000);
	ft_memcpy(str, name, strlen(name));
	free(name);
	while (1)
	{
		signal(SIGINT, ft_heredoc_ctrlc);
		prompt = readline("> ");
		if (!prompt)
			print_error("warning: here-document delimited by end-of-file", 0);
		else if (ft_strcmp(prompt, str))
		{
			i = ft_heredoc_loop2(prompt);
			continue ;
		}
		if (prompt)
			free(prompt);
		break ;
	}
	return (i);
}

// static int	update_heredoc(char *str)
// {
// 	int		tmp;

// 	tmp = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (tmp < 0)
// 		return (1);
// 	ft_putstr_fd(str, tmp);
// 	close(tmp);
// 	free(str);
// 	return (0);
// }

int	ft_heredoc_child(char *name, t_shell *shell)
{
	int					i;

	i = 0;
	ft_free_heredoc(shell);
	signal(SIGQUIT, SIG_IGN);
	i = ft_heredoc_loop(name);
	return (i);
}

int	ft_heredoc_read(char *name)
{
	int		tmp;

	tmp = open(name, O_RDONLY);
	if (tmp < 0)
		return (1);
	unlink(name);
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	return (0);
}

/* int	ft_heredoc_main(char *name)
{
	pid_t	pid;
	int	status;

	// tmp_fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// save_fd = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		exit(ft_heredoc_child(name));
	else if (pid < 0)
	{
		ft_putstr_fd("minishell: fork: ", STDERR_FILENO);
		g_signal_exit = 2;
	}
	update_signal(pid, &status);
	ft_heredoc_read(status);
	return (0);
}
 */
int	ft_input_redirect(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	dup2(fd, IN);
	close(fd);
	return (0);
}

int	ft_output_redirect(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	dup2(fd, OUT);
	close(fd);
	return (0);
}

int	ft_output_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	dup2(fd, OUT);
	close(fd);
	return (0);
}

int	ft_redir_type(char *name, char *str)
{
	if (ft_strcmp("<", str) == 0)
		return (ft_input_redirect(name));
	else if (ft_strcmp("<<", str) == 0)
		return (ft_heredoc_read(name));
	else if (ft_strcmp(">", str) == 0)
		return (ft_output_redirect(name));
	else if (ft_strcmp(">>", str) == 0)
		return (ft_output_append(name));
	else
		return (0);
}
