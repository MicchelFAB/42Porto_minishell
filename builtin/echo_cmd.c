#include "../inc/minishell.h"

extern int		g_signal_exit;

void	print_echo(char **cmd, int i, int flag)
{
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 1)
		printf("\n");
}

void	echo_cmd(char **cmd)
{
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	if(!cmd || !*cmd)
	{
		printf("\n");
		return ;
	}
	if (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		flag = 0;
		i++;
	}
	print_echo(cmd, i, flag);
}
