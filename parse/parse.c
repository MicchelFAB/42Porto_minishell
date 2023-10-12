#include "../inc/minishell.h"

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

void	parse_cmd(t_tree *tree, t_tree *tmp, int *std_in, t_shell *shell)
{
	int		fd[2];
	char	**cmd;

	fd[IN] = dup(STDIN_FILENO);
	fd[OUT] = dup(STDOUT_FILENO);
	create_pipe(tmp, std_in);
	//falta verificar se existe redirects
	cmd = create_cmds(tree, tmp);
	execute(cmd, fd, std_in, shell);
	free_split(cmd);
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	dup2(fd[OUT], STDOUT_FILENO);
	close(fd[OUT]);
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
			tree = tree->next;
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
}