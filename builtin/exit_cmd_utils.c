#include "../inc/minishell.h"

int	ft_is_all_digit(char *num)
{
	int		i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_number(char *num)
{
	int		sign;

	sign = 0;
	if (!ft_strlen(num))
		return (0);
	if (*num == '-')
	{
		num++;
		sign = 1;
	}
	if (!*num)
		return (0);
	if (*num == '-' && *(num + 1) == '\0')
		return (1);
	if (!ft_is_all_digit(num))
		return (0);
	if (ft_strlen(num) < 19)
		return (1);
	if (ft_strlen(num) > 19 || (!sign && ft_strcmp("9223372036854775807", num)
			< 0))
		return (0);
	if (ft_strlen(num) > 19 || (sign && ft_strcmp("9223372036854775808", num)
			< 0))
		return (0);
	return (1);
}
