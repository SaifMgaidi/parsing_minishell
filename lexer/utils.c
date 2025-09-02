#include "lexer.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_quotes(int c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	is_operator(char *line)
{
	if (!ft_strncmp(line, ">>", 2))
		return (1);
	else if (!ft_strncmp(line, "<<", 2))
		return (1);
	if (*line == '>' || *line == '<')
		return (1);
	if (*line == '|')
		return (1);
	return (0);
}

void	remove_space(char **line)
{
	char	*l;

	if (!line || !*line)
		return ;
	l = (*line);
	while (is_space(*l) && *l)
		l++;
	(*line) = l;
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
