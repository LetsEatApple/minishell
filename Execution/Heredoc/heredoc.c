/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:46:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/30 18:23:53 by lhagemos         ###   ########.fr       */
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
	//print_node(next);
/* 	if (node->type == HEREDOC || node->type == REDIR_IN)
	{ */
		if (next->type == CMD || next->type == REDIR_OUT || next->type == REDIR_OUT_APPEND)
			return (true);
/* 	}
	else if (node->type == REDIR_OUT || node->type == REDIR_OUT_APPEND)
	{
		if (next->type == CMD || next->type == REDIR_IN || next->type == HEREDOC)
			return (true);
	} */
	return (false);
}

/* void handle_heredoc(t_data *data, t_node *node)
{
	int original_stdin;
	int pid;
	char		*tmp;
	static int	num;
	
	g_signal = 0;
	if (data->doc.file)
	{
		if (access(data->doc.file, F_OK) == 0)
			unlink(data->doc.file);
		free(data->doc.file);
		data->doc.file = NULL;
	}
	tmp = ft_itoa(num);
	data->doc.file = ft_strjoin("temp", tmp);
	{
		free(tmp);
		num++;
	}
	pid = fork();
	if (pid == 0)
	{
		data->doc.delimiter = get_delimiter(node);
		create_docfile(data, data->doc.delimiter);
		exit(1);
	}
	wait(&pid);
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
		//data->std_in_fd = original_stdin;
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
} */

void handle_heredoc(t_data *data, t_node *node)
{
	int original_stdin;

	g_signal = 0;
	data->doc.delimiter = get_delimiter(node);
	if (create_docfile(data, data->doc.delimiter) == false)
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
		//data->std_in_fd = original_stdin;
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
