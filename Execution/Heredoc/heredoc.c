/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:46:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 22:37:25 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handler(int sig)
{
	if (sig == SIGINT)
		g_signal = 130;
}

/* int	get_heredoc(t_data *data, t_node *node)
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
} */

char *get_delimiter(t_node *node)
{
	char *delimiter;

	if (node->prev == NULL && node->right->type == WORD)
		delimiter = node->right->value;
	else if (node->prev == NULL)
		delimiter = node->right->left->value;
	else if (node->right && node->right->type == WORD)
		delimiter = node->right->value;
	else if (node->left && node->left->type == WORD)
		delimiter = node->left->value;
	if (delimiter == NULL)
		return (NULL);
	return (delimiter);
}

t_node	*next_node(t_data *data, t_node *node, t_node *cmd)
{
	if (node->prev == NULL)
	{
		if (node->right->type >= 3 && node->right->type <= 6)
			return(node->right);
		else if (data->root->right->left->type == CMD)
			return(data->root->right->left);
	}
	else
	{
		if (node->prev->type != PIPE)
			return(node->prev);
		else if (node->prev->type == PIPE)
		{
			while (cmd && (cmd->type >= 3 && cmd->type <= 6))
			{
				if (cmd->left && cmd->left->type == CMD)
					break ;
				cmd = cmd->left;
			}
			return(cmd->left);
		}
	}
	return (node);
}

int	check_next_exec(t_data *data, t_node *node)
{
	t_node	*cmd;
	t_node *next;

	cmd = data->root->left;
	if (data->pipes)
		next = next_node(data, node, cmd);
	else
	{
		if ((node->right == NULL || node->right->type == WORD) && data->root->left)
			next = (data->root->left);
		else
		next = node->right;
	}
	print_node(next);
	if (next->type == CMD || next->type == REDIR_OUT || next->type == REDIR_OUT_APPEND)
		return (true);
	else
		return (false);
}

void handle_heredoc(t_data *data, t_node *node)
{
	int original_stdin;

	g_signal = 0;
	data->doc.delimiter = get_delimiter(node);
/* 	ft_putendl_fd(data->doc.delimiter, 2); */
	if (create_docfile(data, data->doc.delimiter) == false)
		return;
	if (node == NULL)
		return;
	//data->heredoc--;
	data->doc.fd = open(data->doc.file, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(data->doc.fd, STDIN_FILENO) == -1)
	{
		close(data->doc.fd);
		ft_perror("dup21", 1);
		return;
	}
	close(data->doc.fd);
	if (check_next_exec(data, node) == true)
	{
		ft_next_exec(data, node);
		if (dup2(original_stdin, STDIN_FILENO) == -1)
		{
			ft_perror("dup23", 1);
			return;
		}
		close(original_stdin);
	}
	else
	{
		if (dup2(original_stdin, STDIN_FILENO) == -1)
		{
			ft_perror("dup23", 1);
			return;
		}
		close(original_stdin);
		ft_next_exec(data, node);
	}
	
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