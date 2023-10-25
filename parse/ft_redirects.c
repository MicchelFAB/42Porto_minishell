#include "minishell.h"

extern int g_signal_exit;

int	ft_heredoc(char *name)
{
	char	*prompt;
	int		fd_in;
	int 	fd_out;

	fd_in = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		prompt = readline("> ");
		while (ft_strcmp(prompt, name))
		{
			ft_putendl_fd(prompt, fd_in);
			free(prompt);
			prompt = readline("> ");
		}
		if (prompt)
			free(prompt);
		fd_out = open(".heredoc", O_RDONLY);
		close(fd_in);
		dup2(fd_out, STDIN_FILENO);
		close(fd_out);
		unlink(".heredoc");
		break;
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
	// char name;
	
	fd = open(file,	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, OUT);
	close(fd);
	return (0);
}

int ft_output_append(char *file)
{
	int fd;

	fd = open(file,	O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, OUT);
	close(fd);
	return (0);
}
