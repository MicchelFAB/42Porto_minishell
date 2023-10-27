/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmvchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:16:15 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/26 15:39:06 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rmvchar(char *str, int pos)
{
	char	*tmp;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = ft_strlen(str);
	if (pos < 0 || pos > size)
		return (str);
	tmp = malloc(sizeof(char) * size);
	while (i < pos)
		tmp[j++] = str[i++];
	i++;
	while (str[i])
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}
