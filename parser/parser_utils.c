#include "parser.h"
#include <stdio.h>

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
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd)
		free_command(node->cmd);
	if (node->filename)
		free(node->filename);
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
	else if (node->type == NODE_REDIR_IN)
		printf("type node: NODE_REDIR_IN\n");
	else if (node->type == NODE_REDIR_OUT)
		printf("type node: NODE_REDIR_OUT\n");
	else if (node->type == NODE_APPEND)
		printf("type node: NODE_APPEND\n");
	else if (node->type == NODE_HEREDOC)
		printf("type node: NODE_HEREDOC\n");
	else if (node->type == NODE_INVALID)
		printf("type node: NODE_INVALID\n");
	if (node->cmd)
	{
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
	if (node->filename)
		printf("filename: %s\n", node->filename);
	if (node->left)
		print_ast_node(node->left);
	if (node->right)
		print_ast_node(node->right);
}
