#include "../inc/minishell.h"

int		cmds_len(t_tree *tree, t_tree *tmp)
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