#include "parser.h"
#include "stdio.h"

size_t	count_token_words(t_token *tokens)
{
	size_t	count;

	if (!tokens)
		return (0);
	count = 0;
	while (tokens)
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

t_command   *create_command(t_token *tokens)
{
	t_command	*cmd;
	size_t		nb_words;

	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	nb_words = count_token_words(tokens);
	cmd->args = create_args(tokens, nb_words);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_ast_node  *parse_simple_command(t_token *tokens)
{
	t_ast_node  *ast_node;

	if (!tokens)
		return (NULL);
	ast_node = malloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	ast_node->type = NODE_COMMAND;
	ast_node->cmd = create_command(tokens);
	if (!ast_node->cmd)
	{
		free(ast_node);
		return (NULL);
	}
	return (ast_node);
}

void	free_command(t_command *cmd)
{
	char	**words;
	size_t	i;

	if (!cmd)
		return ;
	words = cmd->args;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_command(node->cmd);
	free(node);
}

void	print_ast_node(t_ast_node *node)
{
	char	**words;
	size_t	i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		printf("type node: NODE_COMMAND\n");
	printf("args: ");
	words = node->cmd->args;
	i = 0;
	while (words[i])
	{
		printf("%s ", words[i]);
		i++;
	}
	printf("\n");
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
	node = parse_simple_command(tokens);
	print_ast_node(node);
	free_tokens(&tokens);
	free_ast(node);
	return (0);
}
