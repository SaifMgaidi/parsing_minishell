#include <stdlib.h>

int		is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		count_word(char *line)
{
	int		count;
	size_t	i;

	if (!line)
		return (0);
	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && is_space(line[i]))
			i++;
		if (line[i])
			count++;
		while (line[i] && !is_space(line[i]))
			i++;
	}
	return (count);
}

void	free_lines(char **lines, size_t len)
{
	size_t	i;

	if (!lines)
		return ;
	i = 0;
	while (i < len)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
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

char	*get_word(char *line)
{
	size_t	len;

	if (!line)
		return (NULL);
	len = 0;
	while (*line && is_space(*line))
		line++;
	while (line[len] && !is_space(line[len]))
		len++;
	return (ft_strndup(line, len));
}

char	**ft_split_line(char *line)
{
	char	**lines;
	size_t	nb_words;
	size_t	i;

	if (!line)
		return (NULL);
	nb_words = count_word(line);
	lines = malloc(sizeof(char *) * (nb_words + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		while (*line && is_space(*line))
			line++;
		lines[i] = get_word(line);
		if (!lines[i])
		{
			free_lines(lines, i);
			return (NULL);
		}
		while (*line && !is_space(*line))
			line++;
		i++;
	}
	lines[i] = NULL;
	return (lines);
}
