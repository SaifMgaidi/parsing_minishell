#include "lexer.h"
#include <stdio.h>

size_t	get_len_segment_word(char *word)
{
	size_t	len;

	if (!word)
		return (0);
	len = 0;
	if (word[0] != 36)
	{
		while (word[len] != 36 && word[len])
			len++;
	}
	else
	{
		len = 0;
		if (!word[len])
			return (0);
		while (word[len + 1] != 36 && !is_space(word[len + 1])
			&& !is_operator(word + len + 1) && word[len + 1])
			len++;
	}
	return (len);
}

void	set_word_and_type_segment(t_segment *segment, char *word, size_t len)
{
	char	*tmp;
	char	*tmp_getenv;

	if (!segment || !word)
		return ;
	if (word[0] == 36)
		segment->type = 1;
	else
		segment->type = 0;
	if (segment->type == 0)
		segment->word = ft_strndup(word, len);
	else
	{
		tmp = ft_strndup(word + 1, len);
		tmp_getenv = getenv(tmp);
		if (tmp_getenv)
			segment->word = ft_strdup(tmp_getenv);
		else
			segment->word = ft_strdup("");
		free(tmp);
	}
}

t_segment	*create_segments(char *word)
{
	t_segment	*new;
	size_t		len;

	if (!word)
		return (NULL);
	new = malloc(sizeof(t_segment));
	if (!new)
		return (NULL);
	len = get_len_segment_word(word);
	if (!len)
	{
		free(new);
		return (NULL);
	}
	set_word_and_type_segment(new, word, len);
	if (!new->word)
	{
		free(new);
		return (NULL);
	}
	if (new->type == 0)
		new->next = create_segments(word + len);
	else
		new->next = create_segments(word + len + 1);
	return (new);
}

size_t	get_len_from_segments(t_segment *segments)
{
	size_t	len;
	size_t	i;

	if (!segments)
		return (0);
	len = 0;
	while (segments)
	{
		i = 0;
		while (segments->word[i])
		{
			len++;
			i++;
		}
		segments = segments->next;
	}
	return (len);
}

char	*convert_segments_to_str(t_segment *segments)
{
	char	*word;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!segments)
		return (NULL);
	len = get_len_from_segments(segments);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len && segments)
	{
		j = 0;
		while (segments->word[j])
		{
			word[i] = segments->word[j];
			j++;
			i++;
		}
		segments = segments->next;
	}
	word[i] = 0;
	return (word);
}
