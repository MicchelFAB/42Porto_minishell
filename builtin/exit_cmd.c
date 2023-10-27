#include "minishell.h"

extern int		g_signal_exit;

void	ft_exit_two_args(char **cmd, t_shell *shell)
{
	long long	code_num;

	if (ft_is_number(cmd[1]))
	{
		clean_all(shell);
		code_num = (char)ft_atoi(cmd[1]);
		free_split(cmd);
		exit(code_num);
	}
	else
	{
		print_error("numeric argument required", 2);
		clean_all(shell);
		g_signal_exit = 2;
	}
}

void	exit_cmd(char **cmd, t_shell *shell)
{
	int		len;

	len = 0;
	//verificar se é pipe!!!!
	while (cmd[len])
		len++;
	printf("exit\n");
	if (len > 2)
	{
		print_error("too many arguments", 1);
		return ;
	}
	if (len == 1)
		clean_all(shell);
	if (len == 2)
		ft_exit_two_args(cmd, shell);
	free_split(cmd);
	exit(g_signal_exit);
}

char	*ft_exit_nbr(void)
{
	char	*nbr;

	nbr = ft_itoa(g_signal_exit);
	//free(str);
	return (nbr);
}