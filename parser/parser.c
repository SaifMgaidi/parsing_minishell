#include "parser.h"

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
	size_t	i;
	i = 0;
	while (i < nb_words && tokens)
	{
		if (tokens->type == WORD)
		{
			cmd->args[i] = ft_strdup(tokens->value);
		}
	}
}

t_command   *create_command(t_token *tokens)
{
	t_command	*cmd;
	char		**words;
	size_t		nb_words;
	size_t		i;

	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	nb_words = count_token_words(tokens);
	cmd->args = malloc(sizeof(char *) * (nb_words + 1));
	if (!cmd->args)
		return (NULL);
	
	
	
}


t_ast_node  *parse_simple_command(t_token *tokens)
{
	t_ast_node  *ast_node;
	t_token     *current;
	size_t      nb_words;

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