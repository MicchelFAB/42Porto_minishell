#include "minishell.h"

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	printf("\033[31mError: Bad argument\n\e[0m");
	printf("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	printf("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n");
	exit(EXIT_SUCCESS);
}

int		open_file(char *av, int i)
{
	int		file;

	file = 0;
	if (i == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(av, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths);
	return (0);
}

void	execute(char *av, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(av, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

void	child_proc(char *av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if(pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *limiter, int ac)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (ac < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (strncmp(line, limiter, strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write (fd[1], line, strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int		main(int ac, char **av, char **envp)
{
	int		i;
	int		file_in;
	int		file_out;
	
	if (ac >= 5)
	{
		if (strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			file_out = open_file(av[ac - 1], 0);
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			file_out = open_file(av[ac - 1], 1);
			file_in = open_file(av[1], 2);
			dup2(file_in, STDIN_FILENO);
		}
		while (i < ac - 2)
			child_proc(av[i++], envp);
		dup2(file_out, STDOUT_FILENO);
		execute(av[ac - 2], envp);
	}
	usage();
}