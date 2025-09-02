#ifndef PARSER_H
# define PARSER_H

#include "../lexer/lexer.h"

typedef enum e_node_type
{
	NODE_COMMAND
}	t_node_type;

typedef struct s_command
{
	char	**args;
}	t_command;

typedef struct s_ast_node
{
	t_node_type			type;
	t_command			*cmd;
}	t_ast_node;

t_ast_node	*parse_simple_command(t_token *tokens);
void		free_ast(t_ast_node *node);
void		free_command(t_command *cmd);

#endif