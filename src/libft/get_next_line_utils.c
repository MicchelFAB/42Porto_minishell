/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:29:44 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/26 15:41:55 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void			*p;
	unsigned char	*s;
	size_t			len;

	len = nmemb * size;
	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (p);
	s = p;
	while (len--)
		*(s++) = 0;
	return (p);
}
