/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:30:11 by mamaral-          #+#    #+#             */
/*   Updated: 2023/08/08 13:50:58 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dest;
	s = (unsigned char *)src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	if (dest > src)
		while (n--)
			d[n] = s[n];
	return (dest);
}
