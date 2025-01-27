/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:46:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/27 18:26:19 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
		g_signal = 130;
}

int	get_heredoc(t_data *data, t_node *node)
{
	while (node->right && node->right->type == HEREDOC)
	{
		data->doc.delimiter = node->right->left->value;
		create_docfile(data, data->doc.delimiter);
		node = node->right;
	}
	data->doc.delimiter = node->right->value;
	if (create_docfile(data, data->doc.delimiter) == false)
		return (false);
	return (true);
}

void	handle_heredoc(t_data *data, t_node *node)
{
	int		original_stdin;

	g_signal = 0;
	if (get_heredoc(data, node) == false)
		return ;
	if (node == NULL)
		return ;
	data->heredoc--;
	data->doc.fd = open(data->doc.file, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(data->doc.fd, STDIN_FILENO) == -1)
	{
		close(data->doc.fd);
		return ;
	}
	close(data->doc.fd);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}

/* void	create_docfile(t_data *data, char *key)
{
	int		doc;
	char	buffer[100];
	int		i;
	char	*history;

	doc = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	history = data->input;
	data->input = ft_strjoin(data->input, "\n");
	free(history);
	while (1)
	{
		
		write(STDIN_FILENO,"> ", 3);
		i = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (i == -1)
		{
			if (errno == EINTR)
			{
				if( g_signal == 130)
					break ;
			}
			else
			{
				perror("Error reading input");
				return ;
			}
		}
		else
		{
			buffer[i] = '\0';
			history = data->input;
			data->input = ft_strjoin(history, buffer);
			free(history);
			if(ft_strncmp(key, buffer, ft_strlen(key)) == 0)
				break ;
			if (buffer[0] == '\0')
				write (doc, "\n", 1);
			write(doc, buffer, i);
		}
	}
	close(doc);
} */