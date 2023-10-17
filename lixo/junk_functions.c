
#include "minishell.h"

char	*malloc_rd(char *s)
{
	char	*rest;
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (ft_elements(s, i))
			n++;
		i++;
	}
	rest = (char *)malloc(sizeof(char) * (i + 2 * n + 1));
	if (!rest)
		return (NULL);
	ft_bzero(rest, i + 2 * n + 1);
	return (rest);
}

char	*ft_quote_data(char *str, t_shell *line, int *i, int *j)
{
	if (line->line[*i + 1] && line->line[*i + 1] == '\"')
		str[(*j)++] = (char)(line->line[(*i)++]);
	else if (line->line[*i + 1] && line->line[*i + 1] == '\'')
		(*i)++;
	else
	{
		str[*j] = check_next_char(line->line, *i);
		if (str[*j] == -2)
		{
			str = get_merged_str(line, j);
			while (!isspace(line->line[*i]) && line->line[*i] != '\0')
				(*i)++;
		}
	}
	return (str);
}

int	ft_elements(char *s, int i)
{
	if (i > 0 && s[i - 1] == '\\' && ft_strchr("><;|", s[i]))
		return (0);
	else if (ft_strchr("><;|", s[i]) && check_quote_pair(s, i) == 0)
		return (1);
	else
		return (0);
}

char	*ft_rd_instr(char *instr)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char) * 1);
	ft_bzero(temp, 1);
	while (instr[i] && ft_is_special(instr[i]) == 1)
		i++;
	if (instr[i] == '\0')
		return (NULL);
	while (instr[i])
	{
		if (ft_is_special(instr[i]) == 4)
		{
			while (instr[i] && ft_is_special(instr[i]) != 4)
			{
				printf("3");
				i++;
			}
			temp = ft_strjoin(temp, instr + i);
			free(instr);
			break ;
		}
		else if (ft_is_special(instr[i]) == 3)
		{
			while (instr[i] && ft_is_special(instr[i]) != 3)
			{
				if (instr[i] == '$')
				{
					printf("4");
					ft_rd_sign(instr);
					while (instr[i] && ft_is_special(instr[i]) != 1)
						i++;
					temp = ft_strjoin(temp, instr + i);
					free(instr);
				}
			}
		}
		else
			printf("%c", instr[i++]);
	}
	printf("\n");
	return (temp);
}

char	*ft_strjoin_null(char *s1, char *s2)
{
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		result = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
		return (result);
	}
	if (s1 == NULL && s2 != NULL)
	{
		result = ft_strdup(s2);
		free(s2);
		return (result);
	}
	if (s1 != NULL && s2 == NULL)
	{
		result = ft_strdup(s1);
		free(s1);
		return (result);
	}
	return (NULL);
}

long long int	ft_atol(const char *nptr)
{
	long long int	res;
	long long int	sinal;

	res = 0;
	sinal = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		sinal *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * sinal);
}

void	ft_putspecial(char *str, char *line, int *i, int *j)
{
	str[(*j)++] = ' ';
	str[(*j)++] = line[(*i)++];
	if (check_quote_pair(line, *i) == 0
		&& (line[*i] == '>' || line[*i] == '<' || line[*i] == '|'))
		str[(*j)++] = line[(*i)++];
	str[(*j)++] = ' ';
}

char	check_next_char(char *str, int i)
{
	if (str[i + 1] == '?')
		return(-2);
	else if (!(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		return(-3);
	else
		return(-2);
}
