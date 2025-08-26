#ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>
#include "../libft/libft.h"

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

// lexer.c
t_token	*ft_tokenize(char *line);
// lexer_utils.c
char	*get_word(char **line);
#endif