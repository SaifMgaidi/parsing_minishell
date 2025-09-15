#include "lexer.h"
#include <stdio.h>

t_token_type	get_token_type(char *word)
{
	if (!ft_strncmp(word, ">>", 2) && ft_strlen(word) == 2)
		return (APPEND);
	else if (!ft_strncmp(word, "<<", 2) && ft_strlen(word) == 2)
		return (HEREDOC);
	else if (!(ft_strncmp(word, ">", 1)) && ft_strlen(word) == 1)
		return (REDIR_OUT);
	else if (!ft_strncmp(word, "<", 1) && ft_strlen(word) == 1)
		return (REDIR_IN);
	else if (!ft_strncmp(word, "|", 1) && ft_strlen(word) == 1)
		return (PIPE);
	else
		return (WORD);
}

int	create_token(t_token **tokens, char *word)
{
	t_token	*new;
	t_token	*curr;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->value = word;
	if (!new->value)
	{
		free(new);
		return (0);
	}
	new->type = get_token_type(new->value);
	new->next = NULL;
	if (!(*tokens))
		(*tokens) = new;
	else
	{
		curr = (*tokens);
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (1);
}

t_token	*ft_tokenize(char *line)
{
	t_token	*tokens;

	if (!line)
		return (NULL);
	tokens = NULL;
	while (*line)
	{
		if (!create_token(&tokens, get_word(&line)))
		{
			free_tokens(&tokens);
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (NULL);
		}
	}
	return (tokens);
}

const char	*token_type_to_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

int	main(int argc, char *argv[])
{
	t_token	*token;
	t_token	*current;

	if (argc != 2)
		return (0);
	token = ft_tokenize(argv[1]);
	if (!token)
		return (1);
	current = token;
	while (current)
	{
		printf("token type: %s\n", token_type_to_str(current->type));
		printf("token word: %s\n\n", current->value);
		current = current->next;
	}
	free_tokens(&token);
	return (0);
}
