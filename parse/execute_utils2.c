#include "minishell.h"

extern int	g_signal_exit;

int	ft_check_path(char **path, t_shell *shell)
{
	t_env	*env_path;

	env_path = search_path("PATH", shell);
	if (!env_path)
	{
		print_error("PATH", 127);
		return (0);
	}
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
	split_paths = ft_split(path, ':');
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
