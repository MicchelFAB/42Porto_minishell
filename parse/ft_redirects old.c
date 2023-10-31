#include "minishell.h"

extern int	g_signal_exit;

static void	ft_heredoc_child(int fd_in, char *name)
{
	char	*prompt;

	signal(SIGINT, ft_heredoc_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
		{
			print_error("warning: here-document delimited by end-of-file", 0);
			close(fd_in);
			exit(0);
		}
		if (ft_strcmp(prompt, name))
			ft_putendl_fd(prompt, fd_in);
		else
			break ;
		free(prompt);
	}
	close(fd_in);
	free(prompt);
	exit(g_signal_exit);
}

static void	update_heredoc(void)
{
	int		tmp;

	tmp = open(".heredoc", O_RDONLY);
	unlink(".heredoc");
	dup2(tmp, STDIN_FILENO);
	close(tmp);
}

int	ft_heredoc_main(char *name)
{
	int	tmp_fd;
	int	save_fd;
	int	pid;
	int	status;

	tmp_fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	save_fd = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		ft_heredoc_child(tmp_fd, name);
	update_signal(pid, &status);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		tmp_fd = open(".heredoc", O_WRONLY | O_TRUNC, 0644);
		close(tmp_fd);
		g_signal_exit = 130;
	}
	update_heredoc();
	dup2(save_fd, STDOUT_FILENO);
	close(save_fd);
	return (0);
}

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
	dup2(fd, OUT);
	close(fd);
	return (0);
}

int	ft_output_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, OUT);
	close(fd);
	return (0);
}

int	ft_redir_type(char *name, char *str)
{
	if (ft_strcmp("<", str) == 0)
		return (ft_input_redirect(name));
	else if (ft_strcmp("<<", str) == 0)
		return (ft_heredoc_main(name));
	else if (ft_strcmp(">", str) == 0)
		return (ft_output_redirect(name));
	else if (ft_strcmp(">>", str) == 0)
		return (ft_output_append(name));
	else
		return (0);
}
