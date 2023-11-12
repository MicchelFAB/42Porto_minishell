/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:32:25 by mamaral-          #+#    #+#             */
/*   Updated: 2023/10/31 14:55:21 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_join(char *str, char *old, char *new, int i)
{
	char	*start;
	char	*merge;
	char	*end;

	start = ft_substr(str, 0, i);
	merge = ft_strjoin(start, new);
	end = ft_strjoin(merge, str + i + ft_strlen(old));
	free(start);
	free(merge);
	free(str);
	return (end);
}

char	*ft_str_replace(char *str, char *old, char *new, int i)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] == old[j])
			j++;
		if (!old[j])
		{
			str = ft_str_join(str, old, new, i);
			i += ft_strlen(new);
			return (str);
		}
		else
			i++;
	}
	return (str);
}
