#include <stdlib.h>
#include <stdio.h>

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

char	*get_word(char *line)
{
	char	*word;
	size_t	len;
	size_t	i;

	if (!line)
		return (NULL);
	len = 0;
	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	while (line[i] && !is_space(line[i]))
	{
		len++;
		i++;
	}
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_line(char *line)
{
	char	**lines;
	int		nb_words;
	size_t	i;

	if (!line)
		return (NULL);
	nb_words = count_word(line);
	lines = malloc(sizeof(char *) * (nb_words + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		while (is_space(*line))
			line++;
		lines[i] = get_word(line);
		if (!lines[i])
		{
			free_lines(lines, i);
			return (NULL);
		}
		while (!is_space(*line))
			line++;
		i++;
	}
	lines[i] = NULL;
	return (lines);
}
