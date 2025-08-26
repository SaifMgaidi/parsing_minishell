#include "lexer.h"
#include <stdio.h>

int		is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		is_quotes(int c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

char	*ft_strndup(char *str, size_t len)
{
	char	*s;
	size_t	i;

	if (!str)
		return (NULL);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	get_quotes_words(char *line, int *end)
{
	int	c_quotes;

	if (!is_quotes(line[0]))
		return (0);
	c_quotes = *line;
	*end = 1;
	while (line[*end] != c_quotes && line[*end])
		(*end) += 1;
	if (line[*end] != c_quotes)
		return (-1);
	return (1);
}


char	*get_word(char **line)
{
	char	*l;
	char	*word;
	size_t	len;
	int		has_quotes;
	int		end_quotes;

	if (!line || !(*line) || !(**line))
		return (NULL);
	l = (*line);
	len = 0;
	while (*l && is_space(*l))
		l++;
	end_quotes = -1;
	has_quotes = get_quotes_words(l, &end_quotes);
	if (has_quotes > 0)
	{
		word = ft_strndup(l + 1, end_quotes - 1);
		l += end_quotes + 1;
	}
	else if (has_quotes == 0)
	{
		while (l[len] && !is_space(l[len]) && !is_quotes(l[len]))
			len++;
		word = ft_strndup(l, len);
		l += len;
	}
	else
		return (NULL);
	(*line) = l;
	return (word);
}
