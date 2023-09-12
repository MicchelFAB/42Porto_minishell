/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:45:30 by mamaral-          #+#    #+#             */
/*   Updated: 2023/08/22 12:46:26 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinstr(char *s1, char *s2)
{
	char	*dest;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	dest = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!dest)
		return (NULL);
	while (i < len1)
		dest[j++] = s1[i++];
	i = 0;
	while (i < len2)
		dest[j++] = s2[i++];
	dest[j] = '\0';
	free(s1);
	return (dest);
}
