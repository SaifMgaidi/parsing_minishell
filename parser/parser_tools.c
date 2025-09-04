#include "parser.h"

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

t_command	*create_command(t_token *tokens, t_token *stop)
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
