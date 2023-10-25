#include "minishell.h"

extern int g_signal_exit;

int	ft_heredoc(char *name, int fd[])
{
	char	*prompt;
	int		i;

	fd[1] = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		i = open(".heredoc", O_RDONLY);
		prompt = readline("> ");
		while (ft_strcmp(prompt, name))
		{
			ft_putendl_fd(prompt, fd[1]);
			free(prompt);
			prompt = readline("> ");
		}
		if (prompt)
			free(prompt);
		close(i);
		close(fd[1]);
		dup2(fd[0], IN);
		close(fd[0]);
		pipe(fd);
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
