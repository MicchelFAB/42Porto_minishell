#include "../inc/minishell.h"

extern int	g_signal_exit;

char	*ft_strjoin_join(char *key, char *iqual, char *value)
{
	char	*start;
	char	*final;

	if (!key && !iqual && !value)
		return (NULL);
	start = ft_strjoin(key, iqual);
	final = ft_strjoin(start, value);
	free(start);
	return (final);
}

char	**cmd_array(t_shell *shell)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	i = 0;	
	// passar para uma variavel o shell->env
	tmp = shell->env;
	// o numero de estruturas no env
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	// fazer malloc
	envp = ft_calloc(sizeof(char **), i + 1);
	i = 0;
	tmp = shell->env;
	// passar para a variavel envp o que esta no env
	while (tmp)
	{
		envp[i++] = ft_strjoin_join(tmp->key, "=", tmp->value);
		tmp = tmp->next;
	}
	// colocar o final a NULL
	envp[i] = NULL;
	return (envp);
}

int	ft_check_path(char **path, t_shell *shell)
{
	t_env	*env_path;

	// procurar o path no env
	env_path = search_path("PATH", shell);
	// se não houver env 
	if (!env_path)
	{
		print_error("PATH", 127);
		return (0);
	}
	// *path = env->value da linha PATH
	*path = env_path->value;
	return (1);
}

/*
 * vai juntar a path que foi separada com o cmd para se ver se é acessivel
*/

char	*compatible_path(char *split_path, char *cmd)
{
	char	*single_path;
	char	*tmp;

	tmp = ft_strjoin(split_path, "/");
	single_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (single_path);
}

/*
 * vai retornar uma variavel com o caminho pretendido
 * caso comece por '.' ou '/' não faz nada 
*/
char	*get_abs_path(char *cmd, char *path)
{
	char	**split_paths;
	char	*single_path;
	int		i;

	i = 0;
	// vai pegar no PATH e dividir pelo ':'
	split_paths = ft_split(path, ':');
	// vai percurrer a variavel acima e procurar onde o comando seja executavel
	while (split_paths && split_paths[i])
	{
		single_path = compatible_path(split_paths[i], cmd);
		if (access(single_path, F_OK) == 0)
		{
			free_split(split_paths);
			return (single_path);
		}
		free(single_path);
		single_path = NULL;
		i++;
	}
	free_split(split_paths);
	return (single_path);
}

int		cmd_path(char **cmd, int *fd, t_shell *shell)
{
	char	*cmd_abs;
	char	*path;

	(void)fd;
	// verificar se tem cmd[0] e se começa por '.' ou '/'
	if (cmd[0] && (cmd[0][0] == '.' || cmd[0][0] == '/'))
		return (1);
	// verificar se a path está definida no env
	if (!cmd[0] || !ft_check_path(&path, shell))
		return (0);
	// se não for executavel(se acesse != 0)
	if (access(cmd[0], F_OK) != 0)
	{
		// procurar path absoluta para o cmd cmd_abs
		cmd_abs = get_abs_path(cmd[0], path);
		if (!cmd_abs)
		{
			restore_fd(fd);
			print_error("minishell: command not found", 127);
			return (0);
		}
		free(cmd[0]);
		cmd[0] = cmd_abs;
	}
	return (1);
}

void	ft_ctrlc_exec(int sig)
{
	(void)sig;
	printf("\n");
	g_signal_exit = 130;
}

void	ft_ctrl_bslash(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	g_signal_exit = 131;
}

void	ft_exec_signal(void)
{
	signal(SIGINT, ft_ctrlc_exec);
	signal(SIGQUIT, ft_ctrl_bslash);
}

void	error_execve(char **env, char **cmd, t_shell *shell)
{
	free(env);
	free(cmd);
	clean_all(shell);
	printf("command not found\n");
	exit(127);
}

/*
*	verificar se cmd existe e se o PATH existe e fazer o split pelo :
*	se for process child (pid == 0)
*/
void	exec_cmd(char **cmd, int *fd, int *std_in, t_shell *shell)
{
	char	**envp;
	int		pid;

	
	if (!cmd[0] || !cmd_path(cmd, fd, shell))
		return ;
	pid = fork();
	ft_exec_signal();
	shell->pid = pid;
	shell->child_proc++;
	if (pid == 0)
	{
		close(fd[IN]);
		close(fd[OUT]);
		//fechar std_in se for depois da 1 passagem
 		if (*std_in != 0)
			close (*std_in);
		// criar, para colocar no execve, um char ** onde tem o shell->env
		envp = cmd_array(shell);
		if (execve(cmd[0], cmd, envp) == -1)
			error_execve(envp, cmd, shell);
	}
}

void	execute(char **cmd, int *fd, int *std_in, t_shell *shell)
{
	(void)fd;
	(void)std_in;
	if (is_builtin(cmd))
		exec_builtin(&cmd[0], shell);
	else
		exec_cmd(&cmd[0], fd, std_in, shell);
}