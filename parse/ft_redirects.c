#include "minishell.h"

extern int	g_signal_exit;

int	ft_heredoc(char *name)
{
	char	*prompt;
	int		fd[2];

	fd[1] = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// signal(SIGINT, ft_heredoc_ctrlc);
	while (1)
	{
		prompt = readline("> ");
		if (prompt && ft_strcmp(prompt, name))
		{
			ft_putendl_fd(prompt, fd[1]);
			free(prompt);
			continue ;
		}
		if (prompt)
			free(prompt);
		fd[0] = open(".heredoc", O_RDONLY);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		unlink(".heredoc");
		break ;
	}
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
		return (ft_heredoc(name));
	else if (ft_strcmp(">", str) == 0)
		return (ft_output_redirect(name));
	else if (ft_strcmp(">>", str) == 0)
		return (ft_output_append(name));
	else
		return (0);
}
