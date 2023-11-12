/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_especial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:35:17 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/09 11:08:24 by bmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_exit;

/** @brief This code skips an escape sequence in a string. If the current     **
 ** character is a backslash, it is skipped. If the current character is a    **
 ** double quote, the function returns. Otherwise, the function continues to  **
 ** the next character. This function is used to skip escape sequences in the **
 ** string following the first double quote in a double quoted string, which  **
 ** is the  only place where escape sequences are valid.                      **
 ** @param s The string to skip escape sequences in.                          **
 ** @param i The index of the current character in the string.                **
 */
void	ft_skip_escape(char *s, int *i)
{
	while (s[*i] != '\"' && s[*i])
	{
		if (s[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	if (s[*i] == '\"')
		(*i)++;
}

/** @brief This code checks if there are any pipes in our command line. If    **
 ** there are pipes in our command line, if the pipe is the first element of  **
 ** the list it prints error and returns the error number, while the list     **
 ** exists, if there is a sequence of pipes or if the pipe is the last        **
 ** element of the list is a pipe it prints error and returns the error       **
 ** number, else return 0. This function is used to check if there are pipes  **
 ** in our command line that not follow the syntax.                           **
 ** @param shell The shell structure.                                         **
 */
int	ft_check_pipe(t_shell *shell)
{
	t_tree	*tmp;

	if (!shell->tree)
		return (0);
	tmp = shell->tree;
	if (tmp->type == PIPE)
	{
		print_error("syntax error near unexpected token `|'", 2, "minishell:");
		return (g_signal_exit);
	}
	while (tmp)
	{
		if (tmp->type == PIPE && (!tmp->next || tmp->next->type == PIPE
				|| !ft_strcmp(tmp->str1, "||")))
		{
			print_error("syntax error near unexpected token `|'", 2,
				"minishell:");
			return (g_signal_exit);
		}
		tmp = tmp->next;
	}
	return (0);
}

/** @brief This code checks if there are any special characters in our command**
 ** line. If the character is a quote it will be removed, if the character is **
 ** a backslash it will ignore the next character, if the character is a      **
 ** redirection it will check if the next character is a heredoc redirection, **
 ** if it is, and is followed by command it will open the heredoc file. This  **
 ** function is used to check if there are special characters in our command  **
 ** line and give them the correct treatment.                                 **
 ** @param shell The shell structure.                                         **
 */
int	ft_convert_especial(t_shell *shell)
{
	t_tree	*tmp;

	tmp = shell->tree;
	while (tmp)
	{
		if (ft_strchr(tmp->str1, '\'') || ft_strchr(tmp->str1, '\"'))
			tmp->str1 = ft_remove_quotes(tmp->str1);
		if (ft_strchr(tmp->str1, '\\'))
			tmp->str1 = ft_ignore_special(tmp->str1);
		if (tmp->type == REDIR && !ft_strcmp(tmp->str1, "<<"))
		{
			if (tmp->next && tmp->next->type != WORD)
			{
				print_error("syntax error near token `<<'", 2, "minishel");
				return (1);
			}
			ft_heredoc_open(shell, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

/** @brief This function is used to handle the SIGINT signal in the heredoc   **
 ** mode. When the SIGINT signal is received, the function prints the         **
 ** heredoc prompt and resets the buffer.                                     **
 ** @param sig The signal number.                                             **
 ** @param ptr The heredoc structure.                                         **
 */
void	ft_signals_heredoc(t_heredoc *ptr)
{
	signal(SIGINT, (void *)ft_heredoc_ctrlc);
	ft_heredoc_ctrlc(-1, ptr);
}

/** @brief This code checks if there are any tilde in our command line. While 
 ** the list exists, if the tilde exists and dont have quotes
 is the first element of the list it returns 1, else return 0. This 
*/
int	ft_check_tilde(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '~')
		{
			if (check_quote_pair(line, i))
				return (0);
			else if ((i && line [i - 1] == ' ') && (line [i + 1] == ' '
					|| line[i + 1] == '/' || line[i + 1] == '\0'))
				return (1);
		}
		i++;
	}
	return (0);
}
