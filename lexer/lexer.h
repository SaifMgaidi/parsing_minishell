#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"

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

// extract_word.c
char	*extract_word_without_quotes(char **l);
char	*extract_word_simple_quotes(char **l);
char	*extract_word_double_quotes(char **l);
char	*extract_operator(char **l);

// utils.c
int		is_space(int c);
int		is_quotes(int c);
int		is_operator(char *line);
void	remove_space(char **line);
char	*ft_strndup(char *str, size_t len);
#endif