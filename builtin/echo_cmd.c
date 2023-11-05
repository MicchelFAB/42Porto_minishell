#include "minishell.h"

extern int		g_signal_exit;

int		ft_check_n_line(char **cmd, int *k)
{
	int		j;
	int		i;
	int		flag;

	flag = 1;
	i = 0;
	while (cmd[i] && (cmd[i][0] == '-'))
	{
		j = 1;
		while (cmd[i][j] == 'n' && cmd[i][j])
			j++;
		if (cmd[i][j] == '\0')
		{
			flag = 0;
			i++;
			continue ;
		}
		else if (cmd[i][j] != 'n')	
		 	break ;
	}
	*k = i;
	return (flag);
}

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
	if (!cmd || !*cmd)
	{
		printf("\n");
		return ;
	}
	flag = ft_check_n_line(cmd, &i);
	print_echo(cmd, i, flag);
}
