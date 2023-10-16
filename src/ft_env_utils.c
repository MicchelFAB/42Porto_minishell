#include "../inc/minishell.h"

t_env	*search_env(char *key, t_shell *shell)
{
	t_env	*search;

	search = shell->env;
	while (search != NULL)
	{
		if (ft_strcmp(key, search->key) == 0)
			return (search);
		search = search->next;
	}
	return (NULL);
}

int	ft_set_env(char *key, char *new_val, t_shell *shell)
{
	t_env	*new_env;
	t_env	*search;

	search = search_env(key, shell);
	if (search)
	{
		free(search->value);
		search->value = ft_strdup(new_val);
		return (0);
	}
	else
	{
		new_env = ft_envnew(key, new_val);
		ft_addenv_back(&shell->env, new_env);
		return (0);
	}
	return (-1);
}