#include "minishell.h"

char	*catch_name(t_tree *tree)
{
	char	*name;

	while (tree->type != REDIR)
		tree = tree->next;
	name = ft_strdup(tree->next->str1);
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
	while (tree != tmp && tree->type != REDIR)
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
	while (tree != tmp && tree->type != REDIR)
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
