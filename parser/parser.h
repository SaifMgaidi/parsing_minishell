#ifndef PARSER_H
# define PARSER_H

#include "../lexer/lexer.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_REDIR_IN,
	NODE_REDIR_OUT
}	t_node_type;

typedef struct s_command
{
	char	**args;
}	t_command;

typedef struct s_ast_node
{
	t_node_type			type;
	t_command			*cmd;
	char				*filename;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*parse_command(t_token *tokens);

// parser_utils.c:
void		free_ast(t_ast_node *node);
void		free_command(t_command *cmd);
void		print_ast_node(t_ast_node *node);

#endif