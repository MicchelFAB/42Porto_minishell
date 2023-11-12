/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:01:22 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/08 11:24:16 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp = shell->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = ft_calloc(sizeof(char **), i + 1);
	i = 0;
	tmp = shell->env;
	while (tmp)
	{
		envp[i++] = ft_strjoin_join(tmp->key, "=", tmp->value);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

// verificar se tem cmd[0] e se começa por '.' ou '/'
// verificar se a path está definida no env
// se não for executavel(se acesse != 0)
// procurar path absoluta para o cmd cmd_abs

int	cmd_path(char **cmd, int *fd, t_shell *shell)
{
	char	*cmd_abs;
	char	*path;

	(void)fd;
	if (cmd[0] && (cmd[0][0] == '.' || cmd[0][0] == '/'))
		return (1);
	if (!cmd[0] || !ft_check_path(&path, shell))
		return (0);
	if (access(cmd[0], F_OK) != 0)
	{
		cmd_abs = get_abs_path(cmd[0], path);
		if (!cmd_abs)
		{
			restore_fd(fd);
			print_error("command not found", 127, cmd[0]);
			return (0);
		}
		free(cmd[0]);
		cmd[0] = cmd_abs;
	}
	return (1);
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
		close(STDERR_FILENO);
		if (*std_in != 0)
			close (*std_in);
		envp = cmd_array(shell);
		if (execve(cmd[0], cmd, envp) == -1)
			error_execve(envp, cmd, shell);
	}
}

void	execute(char **cmd, int *fd, int *std_in, t_shell *shell)
{
	if (is_builtin(cmd))
		exec_builtin(&cmd[0], fd, shell);
	else
		exec_cmd(&cmd[0], fd, std_in, shell);
}
