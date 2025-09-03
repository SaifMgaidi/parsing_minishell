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
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	nb_words = count_token_words(tokens, stop);
	cmd->args = create_args(tokens, nb_words);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_token	*find_redirections_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
			return (tokens);
		if (tokens->type == REDIR_OUT)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}


t_ast_node	*parse_command_with_redirections(t_token *tokens)
{
	t_ast_node	*ast_node;
	t_token		*redir_token;

	if (!tokens)
		return (NULL);
	ast_node = malloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	ft_memset(ast_node, 0, sizeof(t_ast_node));
	redir_token = find_redirections_token(tokens);
	if (redir_token->type == REDIR_IN)
		ast_node->type = NODE_REDIR_IN;
	if (redir_token->type == REDIR_OUT)
		ast_node->type = NODE_REDIR_OUT;
	ast_node->filename = ft_strdup(redir_token->next->value);
	if (!ast_node->filename)
	{
		free_ast(ast_node);
		return (NULL);
	}
	ast_node->cmd = create_command(tokens, redir_token);
	if (!ast_node->cmd)
	{
		free_ast(ast_node);
		return (NULL);
	}
	return (ast_node);
}

t_ast_node  *parse_simple_command(t_token *tokens)
{
	t_ast_node  *ast_node;

	if (!tokens)
		return (NULL);
	ast_node = malloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	ft_memset(ast_node, 0, sizeof(t_ast_node));
	ast_node->type = NODE_COMMAND;
	ast_node->cmd = create_command(tokens, NULL);
	if (!ast_node->cmd)
	{
		free(ast_node);
		return (NULL);
	}
	return (ast_node);
}

int	has_redirections(t_token *tokens)
{
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
			return (1);
		if (tokens->type == REDIR_OUT)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

t_ast_node	*parse_command(t_token *tokens)
{
	if (!has_redirections(tokens))
		return (parse_simple_command(tokens));
	else
		return (parse_command_with_redirections(tokens));
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
	node = parse_command(tokens);
	print_ast_node(node);
	free_tokens(&tokens);
	free_ast(node);
	return (0);
}
