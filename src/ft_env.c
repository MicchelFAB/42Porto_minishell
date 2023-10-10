#include "../inc/minishell.h"

extern int g_signal_exit;

void	ft_addenv_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = *lst;
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void print_cmdenv(t_shell *shell)
{
	t_env *tmp;

	tmp = shell->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_signal_exit = 0;
}

void ft_freeenv(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*ft_envnew(char *key, char *value)
{
	t_env *new_env;
	
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		return (NULL);
	}
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	return (new_env);
	}


void ft_import_env(t_shell *shell, char **env)
{
	t_env	*new;
	int i;
	size_t size;
	char *key;
	char *value;

	i = 0;
	shell->env = NULL;
	while(env[i])
	{
		if(strchr(env[i], '='))
		{
			size = ft_strlen_at(env[i], '=');
			key = malloc(size + 1);
			ft_memcpy(key, env[i], size);
			key[size] = '\0';
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
			new = ft_envnew(key, value);
			new->next = NULL;
			ft_addenv_back(&shell->env, new);
			free(key);
			free(value);
		}
		i++;
	}
}