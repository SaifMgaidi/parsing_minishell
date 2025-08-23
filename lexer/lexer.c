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


t_token_type	get_token_type(char *word)
{
	if (!ft_strncmp(word, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(word, "<<", 2))
		return (HEREDOC);
	else if (!(ft_strncmp(word, ">", 1)))
		return (REDIR_OUT);
	else if (!ft_strncmp(word, "<", 1))
		return (REDIR_IN);
	else if (!ft_strncmp(word, "]", 1))
		return (PIPE);
	else
		return (WORD);

}


int	create_token(t_token **tokens, char *word)
{
	t_token	*tok;

	if (!tokens)
		return (0);
	if (!(*tokens))
	{
		tok = malloc(sizeof(t_token));
		if (!tok)
			return (0);
		(*tokens) = tok;
	}
	else
	{
		tok = (*tokens);
		while (tok->next)
			tok = tok->next;
		tok->next = malloc(sizeof(t_token));
		if (!(tok->next))
			return (0);
		tok = tok->next;
	}
	tok->value = ft_strdup(word);
	if (!tok->value)
	{
		free(tok);
		return (0);
	}
	tok->type = get_token_type(tok->value);
	tok->next = NULL;
	return (1);
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
	tokens = NULL;
	i = 0;
	while (words[i])
	{
		if (!create_token(&tokens, words[i]));
			break ;
		i++;
	}
	return (tokens);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	printf("number words: %d\n", count_word(argv[1]));
	return (0);
}