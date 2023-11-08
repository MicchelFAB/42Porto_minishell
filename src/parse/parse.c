/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonteir <bmonteir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:01:14 by bmonteir          #+#    #+#             */
/*   Updated: 2023/11/08 10:53:28 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

static void	create_pipe(t_tree *tmp, int *std_in)
{
	int		new_fd[2];

	dup2(*std_in, STDIN_FILENO);
	if (*std_in != STDIN_FILENO)
		close(*std_in);
	if (!tmp)
		return ;
	pipe(new_fd);
	dup2(new_fd[OUT], STDOUT_FILENO);
	close(new_fd[OUT]);
	*std_in = new_fd[IN];
}

int	ft_redir(t_tree *tree)
{
	t_tree	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = tree;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR)
		{
			str = catch_name(tmp);
			if (!str)
				return (1);
			i = ft_redir_type(str, tmp->str1);
			if (str)
				free(str);
		}
		tmp = tmp->next;
	}
	return (i);
}

void	parse_cmd(t_tree *tree, t_tree *tmp, int *std_in, t_shell *shell)
{
	int		fd[2];
	char	**cmd;

	fd[IN] = dup(STDIN_FILENO);
	fd[OUT] = dup(STDOUT_FILENO);
	create_pipe(tmp, std_in);
	if (!ft_redir(tree))
	{
		cmd = create_cmds(tree, tmp);
		execute(cmd, fd, std_in, shell);
		free_split(cmd);
	}
	restore_fd(fd);
}

void	parse_pipe(t_tree *tree, int *std_in, t_shell *shell)
{
	t_tree	*tmp;

	tmp = tree;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			parse_cmd(tree, tmp, std_in, shell);
			tree = tmp->next;
			parse_pipe(tree, std_in, shell);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		parse_cmd(tree, tmp, std_in, shell);
}

void	parse_execute(t_shell *shell)
{
	int		std_in;

	if (!shell->tree)
		return ;
	std_in = STDIN_FILENO;
	parse_pipe(shell->tree, &std_in, shell);
	if (std_in != 0)
	{
		dup2(std_in, 0);
		close(std_in);
	}
}
