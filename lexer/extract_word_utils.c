#include "lexer.h"
#include <stdio.h>

char	*get_word_expand(char *line, size_t len)
{
	char	*word;
	char	*word_expand;

	word = ft_strndup(line + 1, len - 1);
	if (!word)
		return (NULL);
	word_expand = getenv(word);
	if (word_expand == NULL)
		word_expand = ft_strdup("");
	else
		word_expand = ft_strdup(word_expand);
	free(word);
	return (word_expand);
}

char	*get_word_in_double_quotes(char *line, size_t len)
{
	char		*word;
	char		*tmp;
	t_segment	*segments;

	tmp = ft_strndup(line + 1, len - 1);
	if (ft_strlen(tmp) == 1 && tmp[0] == '$')
	{
		word = tmp;
		return (word);
	}
	segments = create_segments(tmp);
	word = convert_segments_to_str(segments);
	free(tmp);
	free_segments(segments);
	return (word);
}
