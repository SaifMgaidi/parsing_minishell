#include "lexer.h"

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
