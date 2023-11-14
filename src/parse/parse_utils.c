/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:01:02 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/14 18:45:25 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

char	*catch_name(t_tree *tree)
{
	char	*name;

	while (tree->type != REDIR)
		tree = tree->next;
	if (!tree->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_signal_exit = 2;
		return (NULL);
	}
	name = ft_strdup(tree->next->str1);
	tree->next->type = FILE;
	return (name);
}

void	restore_fd(int *fd)
{
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	dup2(fd[OUT], STDOUT_FILENO);
	close(fd[OUT]);
}

int	cmds_len(t_tree *tree, t_tree *tmp)
{
	int		len;

	len = 0;
	while (tree != tmp)
	{
		if (tree->type == WORD)
			len ++;
		tree = tree->next;
	}
	return (len);
}

char	**cmds_array(t_tree *tree, t_tree *tmp, char **cmd)
{
	int		len;

	len = 0;
	while (tree != tmp)
	{
		if (tree->type == WORD)
		{
			cmd[len] = ft_strdup(tree->str1);
			len ++;
		}
		tree = tree->next;
	}
	return (cmd);
}

char	**create_cmds(t_tree *tree, t_tree *tmp)
{
	char	**cmd;
	int		len;

	len = cmds_len(tree, tmp);
	cmd = (char **)malloc(sizeof(char *) * (len + 1));
	cmd[len] = NULL;
	cmd = cmds_array(tree, tmp, cmd);
	return (cmd);
}
