#include "../inc/minishell.h"

/*
 * se lst stiver vazio 
 * ou o 1 elemento da lst->key é >= que o new->key
 * novo elemento é inserido no inicio
 * else: encontra a posição correta na lista para ser colocado
*/
void	ft_addexp(t_exp **lst, t_exp *new)
{
	t_exp	*cur;

	if (*lst == NULL || ft_strcmp((*lst)->key, new->key) >= 0)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		cur = *lst;
		while (cur->next && ft_strcmp(cur->next->key, new->key) < 0)
			cur = cur->next;
		new->next = cur->next;
		cur->next = new;		
	}
}

void	ft_freeexp(t_exp *exp)
{
	t_exp *tmp;

	while (exp)
	{
		tmp = exp->next;
		free(exp->key);
		free(exp->value);
		free(exp);
		exp = tmp;
	}
}

t_exp	*ft_expnew(void *key, void *value)
{
	t_exp	*new_exp;

	new_exp = malloc(sizeof(t_exp));
	if (!new_exp)
		return (0);
	new_exp->key = ft_strdup(key);
	new_exp->value = ft_strdup(value);
	new_exp->next = NULL;
	return (new_exp);
}

void	ft_import_exp(char **env, t_shell *shell)
{
	char	*key;
	char	*value;
	t_exp	*new;
	int		i;
	int		size;

	i = 0;
	shell->exp = NULL;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			size = ft_strlen_at(env[i], '=');
			key = malloc(size + 1);
			ft_memcpy(key, env[i], size);
			key[size] = '\0';
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
			new = ft_expnew(key, value);
			new->next = NULL;
			ft_addexp(&shell->exp, new);
			free(key);
			free(value);
		}
		i++;
	}
}