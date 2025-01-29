/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:38:03 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 12:58:50 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_data *data, t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == PIPE)
		handle_pipe(data, node);
	else if (node->type == REDIR_IN)
		handle_redir_in(data, node);
	else if (node->type == REDIR_OUT || node->type == REDIR_OUT_APPEND)
		handle_redir_out(data, node);
	else if (node->type == HEREDOC)
		handle_heredoc(data, node);
	else if (node->type == CMD)
		ft_command(data, node->cmd);
}

void	ft_next_exec(t_data *data, t_node *node)
{
	t_node	*cmd;

	cmd = data->root->left;
	if (data->pipes)
		pipes_exec(data, node, cmd);
	else
		no_pipes_exec(data, node);
}
void	pipes_exec(t_data *data, t_node *node, t_node *cmd)
{
	if (node->prev == NULL)
	{
		if (node->right->type >= 3 && node->right->type <= 6)
			execute(data, node->right);
		else if (data->root->right->left->type == CMD)
			execute(data, data->root->right->left);
	}
	else
	{
		if (node->prev->type != PIPE)
			execute(data, node->prev);
		else if (node->prev->type == PIPE)
		{
			while (cmd && (cmd->type >= 3 && cmd->type <= 6))
			{
				if (cmd->left && cmd->left->type == CMD)
					break;
				cmd = cmd->left;
			}
			execute(data, cmd->left);
		}
	}
}

void	no_pipes_exec(t_data *data, t_node *node)
{
	if ((node->right == NULL || node->right->type == WORD) && data->root->left)
		execute(data, data->root->left);
	else
		execute(data, node->right);
}

void	handle_pipe(t_data *data, t_node *node)
{
	int		fd[2];
	pid_t	leftpid;
	pid_t	rightpid;
	t_node	*first_op;

	first_op = node->left;
	if (pipe(fd) == -1)
		perror("pipe");
	leftpid = fork();
	if (leftpid < 0)
		perror("fork");
	if (leftpid == 0)
	{
		dup_exec(fd[0], fd[1], STDOUT_FILENO);
		while (first_op && (first_op->type >= 3 && first_op->type <= 6))
		{
			if (first_op->left && first_op->left->type == CMD)
				break;
			first_op = first_op->left;
		}
		execute(data, first_op);
	//	close(data->std_out_fd);
		exit(g_signal);
	}
	waitpid(leftpid, NULL, 0);
	rightpid = fork();
	if (rightpid < 0)
		perror("fork");
	if (rightpid == 0)
	{
		dup_exec(fd[1], fd[0], STDIN_FILENO);
		execute(data, node->right);
	//	close(data->std_out_fd);
		exit(g_signal);
	}
	close_wait(fd[0], fd[1], leftpid, rightpid);
}

void	dup_exec(int close_fd, int dup_fd, int std)
{
	close(close_fd);
	if (dup2(dup_fd, std) == -1)
	{
		ft_perror("dup2", 1);
		return ;
	}
	close(dup_fd);
}

void	close_wait(int read, int write, pid_t left, pid_t right)
{
	int	status;

	status = 0;
	close(read);
	close(write);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	g_signal = WEXITSTATUS(status);
}
