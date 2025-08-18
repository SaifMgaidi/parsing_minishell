#include "lexer.h"
#include <stdio.h>

int	count_words(char **words)
{
	int	count;

	if (!words)
		return (0);
	count = 0;
	while (words[count])
		count++;
	return (count);
}

t_token	*ft_tokenize(char *line)
{
	char	**words;
	t_token	*tokens;
	size_t	len_words;
	size_t	i;

	if (!line)
		return (NULL);
	words = split_line(line);
	if (!words)
		return (NULL);
	len_words = count_words(words);
	tokens = malloc(sizeof(t_token) * len_words);
	if (!tokens)
	{
		free(words);
		return (NULL);
	}
	i = 0;
	while (words[i])
	{
		
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	printf("number words: %d\n", count_word(argv[1]));
	return (0);
}