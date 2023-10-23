/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:37:45 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/19 11:05:26 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr_end(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (i + j);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strstr_init(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
