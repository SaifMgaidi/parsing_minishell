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

/*char    *get_word(char **line)
{
    char    *word;
    char    *temp_word;

    word = ft_strdup("");
    while (**line && !is_space(**line) && !is_operator(*line))
    {
        if (**line == '\'')
            temp_word = extract_word_simple_quotes(line);
        else if (**line == '\"')
            temp_word = extract_word_double_quotes(line);
        else if (**line == '$')
            temp_word = extract_variable(line);
        else
            temp_word = extract_word_without_quotes(line);

        if (!temp_word)
        {
            free(word);
            return (NULL); // Gérer l'erreur
        }
        word = ft_strjoin(word, temp_word); // Une fonction de concaténation qui libère la mémoire
        if (!word)
            return (NULL);
    }
    return (word);
}*/
