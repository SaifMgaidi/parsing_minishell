#include "lexer.h"

int	get_state(int c)
{
	if (c == 39)
		return (1);
	if (c == 34)
		return (2);
	if (c == 36)
		return (3);
	return (0);
}

char	*get_word(char **line)
{
	char	*l;
	char	*word;
	int		state;

	if (!line || !(*line))
		return (NULL);
	remove_space(line);
	l = (*line);
	word = NULL;
	state = get_state(l[0]);
	if (state == 1)
		word = extract_word_simple_quotes(line);
	else if (state == 2)
		word = extract_word_double_quotes(line);
	else if (state == 3)
		word = extract_variable(line);
	else if (is_operator(l))
		word = extract_operator(line);
	else if (state == 0)
		word = extract_word_without_quotes(line);
	remove_space(line);
	return (word);
}
