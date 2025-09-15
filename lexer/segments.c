#include "lexer.h"
#include <stdio.h>

void	update_segments(t_segment **head, t_segment **tail, t_segment *new)
{
	if (!*head)
	{
		(*head) = new;
		(*tail) = new;
	}
	else
	{
		(*tail)->next = new;
		(*tail) = new;
	}
}

t_segment	*create_segments(char *word)
{
	t_segment	*head;
	t_segment	*tail;
	t_segment	*new;
	char		*current;
	size_t		len;

	if (!word || !*word)
		return (NULL);
	current = word;
	head = NULL;
	tail = NULL;
	while (*current)
	{
		len = get_len_segment_word(current);
		new = create_new_segment(head, current, len);
		if (!new)
			return (NULL);
		update_segments(&head, &tail, new);
		if (new->type == 0)
			current += len;
		else
			current += len + 1;
	}
	return (head);
}

/*t_segment	*create_segments(char *word)
{
	t_segment	*new;
	size_t		len;

	len = get_len_segment_word(word);
	if (!len)
		return (NULL);
	new = malloc(sizeof(t_segment));
	if (!new)
		return (NULL);
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
}*/
