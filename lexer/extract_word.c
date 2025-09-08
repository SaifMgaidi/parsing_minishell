#include "lexer.h"
#include <stdio.h>

char	*extract_word_without_quotes(char **l)
{
	char	*word;
	char	*line;
	size_t	len;

	line = (*l);
	if (!l || !*line)
		return (NULL);
	len = 0;
	while (!is_space(line[len]) && !is_operator(line + len)
		&& !is_quotes(line[len]) && line[len])
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
	if (len == 1)
	{
		(*l) += len + 1;
		return (ft_strdup(""));
	}
	if (!line[len])
		return (NULL);
	word = ft_strndup(line + 1, len - 1);
	(*l) += len + 1;
	return (word);
}

char	*extract_word_double_quotes(char **l)
{
	char		*word;
	char		*tmp;
	char		*line;
	t_segment	*segments;
	size_t	len;

	if (!l || !(*l))
		return (NULL);
	line = (*l);
	len = 1;
	while (line[len] != 34 && line[len])
		len++;
	if (len == 1)
	{
		(*l) += len + 1;
		return (ft_strdup(""));
	}
	if (!line[len])
		return (NULL);
	tmp = ft_strndup(line + 1, len - 1);
	segments = create_segments(tmp);
	word = convert_segments_to_str(segments);
	free(tmp);
	free_segments(segments);
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

char	*extract_variable(char **l)
{
	char	*word;
	char	*word_expand;
	char	*line;
	size_t	len;

	if (!l || !(*l))
		return (NULL);
	line = (*l);
	word = NULL;
	len = 1;
	while (!is_space(line[len]) && !is_quotes(line[len])
		&& !is_operator(line + len) && line[len] != 36 && line[len])
		len++;
	word = ft_strndup(line + 1, len - 1);
	if (!word)
		return (NULL);
	word_expand = getenv(word);
	if (word_expand == NULL)
		word_expand = ft_strdup("");
	else
		word_expand = ft_strdup(word_expand);
	(*l) += len;
	free(word);
	return (word_expand);
}
