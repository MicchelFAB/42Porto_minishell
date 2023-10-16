/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:48:20 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/16 14:05:41 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	print_error(char *msg, int error)
{
	g_signal_exit = error;
	printf("%s\n", msg);
}

// char	*ft_rd_instr(char *instr)
// {
//	char	*temp;
//	int		i;

//	i = 0;
//	temp = malloc(sizeof(char) * 1);
//	ft_bzero(temp, 1);
//	while (instr[i] && ft_is_special(instr[i]) == 1)
//		i++;
//	if (instr[i] == '\0')
//		return (NULL);
//	while (instr[i])
//	{
//		if (ft_is_special(instr[i]) == 4)
//		{
//			while (instr[i] && ft_is_special(instr[i]) != 4)
//			{
//				printf("3");
//				i++;
//			}
//			temp = ft_strjoin(temp, instr + i);
//			free(instr);
//			break ;
//		}
//		else if (ft_is_special(instr[i]) == 3)
//		{
//			while(instr[i] && ft_is_special(instr[i]) != 3)
//			{
//				if(instr[i] == '$')
//					{
//						printf("4");
//						// ft_rd_sign(instr);
//						while(instr[i] && ft_is_special(instr[i]) != 1)
//							i++;
//						temp = ft_strjoin(temp, instr + i);
//						free(instr);
//					}
//			}
//		}
//		else
//			printf("%c", instr[i++]);
//	}
//	printf("\n");
//	return(temp);
// }

// char	*ft_strjoin_null(char *s1, char *s2)
// {
//	char	*result;

//	if (s1 != NULL && s2 != NULL)
//	{
//		result = ft_strjoin(s1, s2);
//		free(s1);
//		free(s2);
//		return (result);
//	}
//	if (s1 == NULL && s2 != NULL)
//	{
//		result = ft_strdup(s2);
//		free(s2);
//		return (result);
//	}
//	if (s1 != NULL && s2 == NULL)
//	{
//		result = ft_strdup(s1);
//		free(s1);
//		return (result);
//	}
//	return (NULL);
// }

// long long int	ft_atol(const char *nptr)
// {
//	long long int	res;
//	long long int	sinal;

//	res = 0;
//	sinal = 1;
//	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
//		nptr++;
//	if (*nptr == '-')
//		sinal *= -1;
//	if (*nptr == '-' || *nptr == '+')
//		nptr++;
//	while (*nptr >= '0' && *nptr <= '9')
//	{
//		res = res * 10 + *nptr - '0';
//		nptr++;
//	}
//	return (res * sinal);
// }
