/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:42:31 by mamaral-          #+#    #+#             */
/*   Updated: 2023/08/08 13:50:58 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	char		*b;
	char		*l;

	if (!*little)
		return ((char *)big);
	while (len-- && *big)
	{
		if (*big == *little)
		{
			i = len;
			b = (char *)big + 1;
			l = (char *)little + 1;
			while (i-- && *b && *l && *l == *b)
			{
				++l;
				++b;
			}
			if (*l == '\0')
				return ((char *)big);
		}
		++big;
	}
	return (NULL);
}
