#include "../inc/minishell.h"

extern int		g_signal_exit;

/*  * recebe key que é o que está entre o export e o '='
 * cmd que é o que está depois do '='
 * type */

int	valid_key(char *key, char *cmd, char *type)
{
	int		i;

	i = 0;
	if (!(ft_isalpha(cmd[i]) || cmd[i] == '_'))
	{
		printf("minishell: %s: %s: not a valid identifier\n", type, cmd);
		return (0);
	}
	i++;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
		{
			printf("minishell: %s: %s: not a valid identifier\n", type, key);
			return (0);
		}
		i++;
	}
	return (1);
}

void	make_export(char *cmd, t_shell *shell)
{
	char	*key;
	char	*value;
	int		len;

	len = 0;
	while (cmd[len] != '\0' && cmd[len] != '=')
		len++;
	key = ft_substr(cmd, 0, len);
	if (!valid_key(key, cmd, "export"))
	{
		free(key);
		return ;
	}
	if (cmd[len] != '=')
	{
		ft_set_exp(key, NULL, shell);
		free(key);
		return ;
	}
	value = ft_strdup(cmd + len + 1);
	ft_set_env(key, value, shell);
	ft_set_exp(key, value, shell);
	free(value);
	free(key);
}

void	export_cmd(char **cmd, t_shell *shell)
{
	int		i;

	i = -1;
	if (contains_pipe(shell))
		return ;
	while (cmd[++i])
	{
		make_export(cmd[i], shell);
	}
	g_signal_exit = 0;
}