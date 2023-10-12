#include "../inc/minishell.h"

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

void	(char **cmd, int *fd, int *std_in, t_shell *shell)
{
	char	**envp;
	(void)fd;
	(void)std_in;
	// verificar se cmd existe e se o PATH existe
	if (!cmd[0])
		return ;
	
	// fazer fork

	// refistar os sinais ctrl+c e ctrl+/

	// registar o pid atual e contar processo++

	//se for process child (pid == 0)
		//fechar os fd's
		//fechar std_in se for depois da 1 passagem
		// criar, para colocar no execve, um char ** onde tem o shell->env
	envp = cmd_array(shell);
	//lidar com o execve
	if (execve(cmd[0], cmd, envp) == -1)
		perror("execve");	

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