/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:31 by mamaral-          #+#    #+#             */
/*   Updated: 2023/09/12 09:27:12 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct minishell
{
	char	**env;
	int		fd;
	char	*line;
	int		signal;
}				t_shell;

#endif