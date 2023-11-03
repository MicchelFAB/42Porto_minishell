/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repetition_break.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:22:22 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/03 12:43:18 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_repetition_break(const char *str)
{
	size_t	position;
	size_t	i;

	position = 0;
	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != str[i + 1])
			i++;
		else
		{
			while (str[i] == str[i + 1])
				i++;
			if (str[i + 1] != '\0')
				position = i + 1;
		}
	}
	return (position);
}
