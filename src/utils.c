/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:48:20 by mamaral-          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/10/12 21:56:44 by mamaral-         ###   ########.fr       */
=======
/*   Updated: 2023/10/09 18:31:48 by mamaral-         ###   ########.fr       */
>>>>>>> c9d4cc5 (09-10)
=======
/*   Updated: 2023/10/10 12:01:14 by mamaral-         ###   ########.fr       */
>>>>>>> 8fd3012 (12/10/23)
=======
/*   Updated: 2023/10/12 21:56:44 by mamaral-         ###   ########.fr       */
>>>>>>> bc19d77 (Day End)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_signal_exit;

void	print_error(char *msg, int error)
{
	g_signal_exit = error;
	printf("%s\n", msg);
<<<<<<< HEAD
=======
}

/**
* @brief
* ft_is_special() is a function that checks if the character is a special character.
* return 1 if the character is a space character ;
* return 2 if the character is a special character;
* return 3 if the character is a single quote;
* return 4 if the character is a double quote;
* return 5 if the character is a pipe;
* return 6 if the character is a redirection;
* return 0 if the character is not a special character;
* @param c is the character to be checked.
*/

int ft_is_special(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	else if (c == '$' || c == '%' || c == '?' || c == '&')
		return (2);
	else if (c == '\'')
		return (3);
	else if (c == '\"')
		return (4);
	else if (c == '|')
		return (5);
	else if (c == '>' || c == '<')
		return (6);
	return (0);
>>>>>>> bc19d77 (Day End)
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

<<<<<<< HEAD
char	*ft_strjoin_null(char *s1, char *s2)
{
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		result = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
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
=======
// char	*ft_strjoin_null(char *s1, char *s2)
// {
// 	char	*result;

// 	if (s1 != NULL && s2 != NULL)
// 	{
// 		result = ft_strjoin(s1, s2);
// 		free(s1);
// 		free(s2);
// 		return (result);
// 	}
// 	if (s1 == NULL && s2 != NULL)
// 	{
// 		result = ft_strdup(s2);
// 		free(s2);
// 		return (result);
// 	}
// 	if (s1 != NULL && s2 == NULL)
// 	{
// 		result = ft_strdup(s1);
// 		free(s1);
// 		return (result);
// 	}
// 	return (NULL);
// }

// long long int	ft_atol(const char *nptr)
// {
// 	long long int	res;
// 	long long int	sinal;

// 	res = 0;
// 	sinal = 1;
// 	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
// 		nptr++;
// 	if (*nptr == '-')
// 		sinal *= -1;
// 	if (*nptr == '-' || *nptr == '+')
// 		nptr++;
// 	while (*nptr >= '0' && *nptr <= '9')
// 	{
// 		res = res * 10 + *nptr - '0';
// 		nptr++;
// 	}
// 	return (res * sinal);
// }
>>>>>>> bc19d77 (Day End)
