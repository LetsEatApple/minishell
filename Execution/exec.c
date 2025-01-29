/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:38:03 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 08:35:21 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	execute(t_data *data, t_node *node)
{
//	print_node(node);
	if (node == NULL)
		return ;
	if (node->type == PIPE)
		handle_pipe(data, node);
	else if (node->type == REDIR_IN)
		handle_redir_in(data, node);
	else if (node->type == REDIR_OUT)
		handle_redir_out(data, node);
	else if (node->type == REDIR_OUT_APPEND)
		handle_redir_append(data, node);
	else if (node->type == HEREDOC)
	 	handle_heredoc(data, node);
	else if (node->type == CMD)
		ft_command(data, node->cmd);
}

void	handle_pipe(t_data *data, t_node *node)
{
	int		fd[2];
	pid_t	leftpid;
	pid_t	rightpid;
	t_node	*temp;
	int		status;

	temp = node->left;
	if (pipe(fd) == -1)
		perror("pipe");
	leftpid = fork();
	if (leftpid < 0)
		perror("fork");
	if (leftpid == 0)
	{
		dup_exec(fd[0], fd[1], STDOUT_FILENO);
		while (temp && (temp->type >= 3 && temp->type <= 6))
		{
			if (temp->left && temp->left->type == CMD)
				break;
			temp = temp->left;
		}
		execute(data, temp);
		close(data->std_out_fd);
		exit(g_signal);
	}
	waitpid(leftpid, &status, 0);
	rightpid = fork();
	if (rightpid < 0)
		perror("fork");
	if (rightpid == 0)
	{
		dup_exec(fd[1], fd[0], STDIN_FILENO);
		execute(data, node->right);
		close(data->std_out_fd);
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
