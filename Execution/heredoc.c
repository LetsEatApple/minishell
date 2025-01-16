/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:46:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/15 17:17:06 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	create_docfile(t_data *data, char *key)
{
	char	*heredoc;
	char	*temp;
	int		doc;
	char	*rl;

	temp = data->input;
	data->input = ft_strjoin(data->input, "\n");
	doc = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while(1)
	{
		rl = readline("> ");
		if (rl == NULL)
			heredoc = ft_strdup("\n");
		else
			heredoc = ft_strjoin(rl, "\n");
		temp = data->input;
		data->input = ft_strjoin(data->input, heredoc);
		free(temp);
		if (rl != NULL && ft_strncmp(rl, key, ft_strlen(key)+1) == 0)
		{
			free(rl);
			free(heredoc);
			break;
		}
		free(rl);
		write(doc, heredoc, ft_strlen(heredoc));
		free(heredoc);
	}
	close(doc);
} */

void	create_docfile(t_data *data, char *key)
{
	int		doc;
	char	buffer[100];
	int		i;
	char	*history;

	doc = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	history = data->input;
	data->input = ft_strjoin(data->input, "\n");
	free(history);
	while(1)
	{
		write(STDIN_FILENO,"> ", 3);
		i = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (i == -1)
		{
			perror("Error reading input");
			return ;
		}
		buffer[i] = '\0';
		history = data->input;
		data->input = ft_strjoin(history, buffer);
		free(history);
		if(ft_strncmp(key, buffer, ft_strlen(key)) == 0)
			break ;
		if (g_signal == 130)
			break ;
		if (buffer[0] == '\0')
			write (doc, "\n", 1);
		write(doc, buffer, i);
	}
	close(doc);
}

t_node	*get_curr(t_node *node)
{
	while (node->left->type == HEREDOC)
		node = node->left;
	while (node->right->type == HEREDOC)
		node = node->right;
	return (node);
}

void	handle_heredoc(t_data *data, t_node *node)
{
	char	*key;
	int		doc;
	t_node	*current;
	int		original_stdin;

	if (list_size(data->token_list) == 2)
		key = data->token_list->next->value;
	else
		key = node->right->value;
	create_docfile(data, key);
	if (g_signal == 130)
		return ;
	if (node == NULL)
		return ;
	current = get_curr(node);
	if (!current)
		return ;
	doc = open("temp", O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(doc, STDIN_FILENO) == -1)
	{
		close(doc);
		return ;
	}
	close(doc);
	if (node->left->type == CMD)
		execute(data, node->left);
	else
		execute(data, current->left);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}