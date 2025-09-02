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

int		is_operator(char *line)
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

int		get_state(int c)
{
	if (c == 39)
		return (1);
	if (c == 34)
		return (2);
	return (0);
}

char	*extract_word_without_quotes(char **l)
{
	char	*word;
	char	*line;
	size_t	len;

	line = (*l);
	if (!l || !*line)
		return (NULL);
	len = 0;
	while (!is_space(line[len]) && !is_operator(line + len) && line[len])
		len++;
	word = ft_strndup(line, len);
	(*l) += len;
	return (word);
}

char	*extract_word_simple_quotes(char **l)
{
	char	*word;
	char	*line;
	size_t	len;

	if (!l || !(*l))
		return (NULL);
	line = (*l);
	len = 1;
	while (line[len] != 39 && line[len])
		len++;
	if (!line[len])
		return (NULL);
	word = ft_strndup(line + 1, len - 1);
	(*l) += len + 1;
	return (word);
}

char	*extract_word_double_quotes(char **l)
{
	char	*word;
	char	*line;
	size_t	len;

	if (!l || !(*l))
		return (NULL);
	line = (*l);
	len = 1;
	while (line[len] != 34 && line[len])
		len++;
	if (!line[len])
		return (NULL);
	word = ft_strndup(line + 1, len - 1);
	(*l) += len + 1;
	return (word);
}

char	*extract_operator(char **l)
{
	char	*word;
	char	*line;
	size_t	len;

	if (!l || !(*l))
		return (NULL);
	word = NULL;
	line = (*l);
	len = 0;
	if (!ft_strncmp(line, ">>", 2) || !ft_strncmp(line, "<<", 2))
	{
		word = ft_strndup(line, 2);
		len = 2;
	}
	else if (*line == '>' || *line == '<' || *line == '|')
	{
		word = ft_strndup(line, 1);
		len = 1;
	}
	(*l) += len;
	return (word);
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

char	*get_word(char **line)
{
	char	*l;
	char	*word;
	int		state;

	if (!line || !*line)
		return (NULL);
	remove_space(line);
	l = (*line);
	word = NULL;
	state = get_state(l[0]);
	if (state == 1)
		word = extract_word_simple_quotes(line);
	else if (state == 2)
		word = extract_word_double_quotes(line);
	else if (is_operator(l))
		word = extract_operator(line);
	else if (state == 0)
		word = extract_word_without_quotes(line);
	remove_space(line);
	return (word);
}
