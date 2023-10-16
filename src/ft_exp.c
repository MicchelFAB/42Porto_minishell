<<<<<<< HEAD
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
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:46:45 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/20 10:55:50 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_env	*ft_expnew(char *key, char *value)
{
	t_exp *new_exp;
	
	new_exp = (t_exp *)malloc(sizeof(t_exp));
	if (!new_exp)
	{
		return (NULL);
	}
>>>>>>> 92ed04a (03.10.23)
	new_exp->key = ft_strdup(key);
	new_exp->value = ft_strdup(value);
	new_exp->next = NULL;
	return (new_exp);
}

<<<<<<< HEAD
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
=======
// Function to export a key-value pair
void ft_import_exp(t_shell *shell, char **env)
{
	t_exp	*new;
	int i;
	size_t size;
	char *key;
	char *value;

	i = 0;
	shell->env = NULL;
	while(env[i])
	{
		if(strchr(env[i], '='))
>>>>>>> 92ed04a (03.10.23)
		{
			size = ft_strlen_at(env[i], '=');
			key = malloc(size + 1);
			ft_memcpy(key, env[i], size);
			key[size] = '\0';
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
			new = ft_expnew(key, value);
			new->next = NULL;
<<<<<<< HEAD
			ft_addexp(&shell->exp, new);
=======
			ft_addenv_back(&shell->env, new);
>>>>>>> 92ed04a (03.10.23)
			free(key);
			free(value);
		}
		i++;
	}
<<<<<<< HEAD
=======
}

void	ft_addexp(t_exp **old, t_exp *new)
{
	t_exp	*present;

	if (old == NULL || new == NULL)
		return ;
	if (*old == NULL || ft_strcmp((*old)->key, new->key) >= 0)
	{
		new->next = *old;
		*old = new;
	}
	else
	{
		present = *old;		
		while (present->next != NULL 
			&& ft_strcmp(present->next->key, new->key) < 0)
			present = present->next;
		new->next = present->next;
		present->next = new;
	}
}

// Function to print the exported variables
void ft_printexp(t_exp *head)
{
    t_exp *temp;
	
	temp = head;

	while (temp)
	{
		printf("EXPORT %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}

// Function to free the memory allocated for the linked list
void ft_freeexp(t_exp *head)
{
    t_exp *temp;
	
    while (temp)
    {
        temp = head->next;
        free(head->key);
        free(head->value);
        free(head);
        head = temp;
    }
    head = NULL;
>>>>>>> 92ed04a (03.10.23)
}