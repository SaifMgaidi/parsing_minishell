#include "parser.h"
#include "stdio.h"

size_t	count_token_words(t_token *tokens, t_token *stop)
{
	size_t	count;

	if (!tokens)
		return (0);
	count = 0;
	while (tokens && tokens != stop)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

char	**create_args(t_token *tokens, size_t nb_words)
{
	char	**words;
	size_t	i;

	words = malloc(sizeof(char *) * (nb_words + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < nb_words && tokens)
	{
		if (tokens->type == WORD)
		{
			words[i] = ft_strdup(tokens->value);
			if (!words[i])
			{
				while (i)
					free(words[--i]);
				free(words);
				return (NULL);
			}
			i++;
		}
		tokens = tokens->next;
	}
	words[i] = NULL;
	return (words);
}

t_command   *create_command(t_token *tokens, t_token *stop)
{
	t_command	*cmd;
	size_t		nb_words;

	if (!tokens)
		return (NULL);
	nb_words = count_token_words(tokens, stop);
	if (!nb_words)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = create_args(tokens, nb_words);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_token	*find_redirections_token(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (NULL);
	while (tokens != stop && tokens)
	{
		if (tokens->type == REDIR_IN)
			return (tokens);
		if (tokens->type == REDIR_OUT)
			return (tokens);
		if (tokens->type == APPEND)
			return (tokens);
		if (tokens->type == HEREDOC)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

t_token	*find_pipe_token(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (NULL);
	while (tokens != stop && tokens)
	{
		if (tokens->type == PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

t_ast_node  *parse_simple_command(t_token *tokens, t_token *stop)
{
	t_ast_node  *ast_node;

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


t_node_type	get_type_node(t_token *token)
{
	if (token->type == REDIR_IN)
		return (NODE_REDIR_IN);
	if (token->type == REDIR_OUT)
		return (NODE_REDIR_OUT);
	if (token->type == APPEND)
		return (NODE_APPEND);
	if (token->type == HEREDOC)
		return (NODE_HEREDOC);
	if (token->type == PIPE)
		return (NODE_PIPE);
	return (NODE_INVALID);
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
	ast_node->type = get_type_node(redir_token);
	if (ast_node->type == NODE_INVALID || !redir_token->next || redir_token->next->type != WORD)
	{
		free_ast(ast_node);
		return (NULL);
	}
	
	if (redir_token->next)
		ast_node->filename = ft_strdup(redir_token->next->value);
	if (!ast_node->filename)
	{
		free_ast(ast_node);
		return (NULL);
	}
	ast_node->left = parse_simple_command(tokens, redir_token);
	if (!ast_node->left)
	{
		free_ast(ast_node);
		return (NULL);
	}
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


int	has_redirections(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (0);
	while (tokens != stop && tokens)
	{
		if (tokens->type == REDIR_IN)
			return (1);
		if (tokens->type == REDIR_OUT)
			return (1);
		if (tokens->type == APPEND)
			return (1);
		if (tokens->type == HEREDOC)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	has_pipe(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (0);
	while (tokens != stop && tokens)
	{
		if (tokens->type == PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
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

int	main(int argc, char *argv[])
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
}
