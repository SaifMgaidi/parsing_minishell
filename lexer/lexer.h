#ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
}	t_token;

// Add token to the end of the list
void	ft_token_add_back(t_token **head, t_token *new_token);
t_token	*ft_tokenize(char *line);
char	**split_line(char *line);
#endif