/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:30:00 by mamaral-          #+#    #+#             */
/*   Updated: 2023/08/08 11:56:42 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> 
# include <stdio.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 33
# endif

char	*get_next_line(int fd);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		get_next_line_arg(int fd, char **line);
#endif