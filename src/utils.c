/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:48:20 by mamaral-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/12 21:56:44 by mamaral-         ###   ########.fr       */
=======
/*   Updated: 2023/10/09 18:31:48 by mamaral-         ###   ########.fr       */
>>>>>>> c9d4cc5 (09-10)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	print_error(char *msg, int error)
{
	g_signal_exit = error;
	printf("%s\n", msg);
}
<<<<<<< HEAD
=======

void ft_rd_sign(char *instr)
{
	int i = 0;
	while(instr[i] && instr[i] != '$')
	i++;
	if (instr[i] == '\0')
		return ;
	i++;
	while(instr[i] && ft_is_special(instr[i]) != 1)
	{
		printf("%c", instr[i]);
		i++;
	}
}
char *ft_rd_instr(char *instr)
{
	char *temp;
	int i = 0;

	temp = malloc(sizeof(char) * 1);
	ft_bzero(temp, 1);
	while(instr[i] && ft_is_special(instr[i]) == 1)
		i++;
	if (instr[i] == '\0')
		return (NULL);
	while(instr[i])
	{
		if (ft_is_special(instr[i]) == 4)
		{
			while(instr[i] && ft_is_special(instr[i]) != 4)
			{
				printf("3");
				i++;
			}
			temp = ft_strjoin(temp, instr + i);
			free(instr);
			break;
		}
		else if (ft_is_special(instr[i]) == 3)
		{
			while(instr[i] && ft_is_special(instr[i]) != 3)
			{
				if(instr[i] == '$')
					{
						printf("4");
						// ft_rd_sign(instr);
						while(instr[i] && ft_is_special(instr[i]) != 1)
							i++;
						temp = ft_strjoin(temp, instr + i);
						free(instr);
					}
			}
		}
		else
			printf("%c", instr[i++]);
	}
	printf("\n");
	return(temp);
}

char	*ft_strjoin_null(char *s1, char *s2)
{
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		result = ft_strjoin(s1, s2);
		free(s1);
		// free(s2);
		return (result);
	}
	if (s1 == NULL && s2 != NULL)
	{
		result = ft_strdup(s2);
		free(s2);
		return (result);
	}
	if (s1 != NULL && s2 == NULL)
	{
		result = ft_strdup(s1);
		free(s1);
		return (result);
	}
	return (NULL);
}
>>>>>>> c9d4cc5 (09-10)
