#include "parser.h"
#include "stdio.h"

t_ast_node	*parse_simple_command(t_token *tokens, t_token *stop)
{
	t_ast_node	*ast_node;

	if (!tokens)
		return (NULL);
	ast_node = malloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	ft_memset(ast_node, 0, sizeof(t_ast_node));
	ast_node->type = NODE_COMMAND;
	ast_node->cmd = create_command(tokens, stop);
	if (!ast_node->cmd)
	{
		free(ast_node);
		return (NULL);
	}
	return (ast_node);
}

int	fill_redirections_node(t_ast_node *ast_node, t_token *tokens
	, t_token *redir_token)
{
	if (!ast_node || !redir_token)
		return (0);
	ast_node->type = get_type_node(redir_token);
	if (ast_node->type == NODE_INVALID || !redir_token->next
		|| redir_token->next->type != WORD)
	{
		free_ast(ast_node);
		return (0);
	}
	if (redir_token->next)
		ast_node->filename = ft_strdup(redir_token->next->value);
	if (!ast_node->filename)
	{
		free_ast(ast_node);
		return (0);
	}
	ast_node->left = parse_simple_command(tokens, redir_token);
	if (!ast_node->left)
	{
		free_ast(ast_node);
		return (0);
	}
	return (1);
}

t_ast_node	*parse_command_with_redirections(t_token *tokens, t_token *stop)
{
	t_ast_node	*ast_node;
	t_token		*redir_token;

	if (!tokens)
		return (NULL);
	ast_node = malloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	ft_memset(ast_node, 0, sizeof(t_ast_node));
	redir_token = find_redirections_token(tokens, stop);
	if (!fill_redirections_node(ast_node, tokens, redir_token))
		return (NULL);
	return (ast_node);
}

t_ast_node	*parser_command_with_pipe(t_token *tokens, t_token *stop)
{
	t_ast_node	*ast_node;
	t_token		*pipe_token;

	if (!tokens)
		return (NULL);
	ast_node = malloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	ft_memset(ast_node, 0, sizeof(t_ast_node));
	pipe_token = find_pipe_token(tokens, stop);
	ast_node->type = get_type_node(pipe_token);
	if (ast_node->type == NODE_INVALID)
	{
		free_ast(ast_node);
		return (NULL);
	}
	ast_node->left = parse_command(tokens, pipe_token);
	ast_node->right = parse_command(pipe_token->next, stop);
	if (!ast_node->left || !ast_node->right)
	{
		free_ast(ast_node);
		return (NULL);
	}
	return (ast_node);
}

t_ast_node	*parse_command(t_token *tokens, t_token *stop)
{
	if (has_pipe(tokens, stop))
		return (parser_command_with_pipe(tokens, stop));
	else if (has_redirections(tokens, stop))
		return (parse_command_with_redirections(tokens, stop));
	else
		return (parse_simple_command(tokens, stop));
}

/*int	main(int argc, char *argv[])
{
	t_ast_node	*node;
	t_token		*tokens;

	if (argc != 2)
		return (1);
	tokens = ft_tokenize(argv[1]);
	if (!tokens)
		return (1);
	node = parse_command(tokens, NULL);
	if (!node)
		ft_putstr_fd("parse error\n", 1);
	else
		print_ast_node(node);
	free_tokens(&tokens);
	if (node)
		free_ast(node);
	return (0);
}*/
