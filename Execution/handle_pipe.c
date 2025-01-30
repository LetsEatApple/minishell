/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:28:30 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/30 23:33:01 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_std_exit(t_data *data)
{
	close(data->stdin);
	close(data->stdout);
	exit(g_signal);
}

void	handle_pipe(t_data *data, t_node *node)
{
	int		fd[2];
	pid_t	leftpid;
	pid_t	rightpid;

	if (pipe(fd) == -1)
		perror("pipe");
	leftpid = fork();
	if (leftpid < 0)
		perror("fork");
	if (leftpid == 0)
	{
		exec_left_pipe(data, node, fd[0], fd[1]);
		close_std_exit(data);
	}
	wait(&leftpid);
	rightpid = fork();
	if (rightpid < 0)
		perror("fork");
	if (rightpid == 0)
	{
		dup_exec(fd[1], fd[0], STDIN_FILENO);
		execute(data, node->right);
		close_std_exit(data);
	}
	close_wait(fd[0], fd[1], leftpid, rightpid);
}

void	exec_left_pipe(t_data *data, t_node *node, int close, int dup)
{
	t_node	*first_op;

	first_op = node->left;
	dup_exec(close, dup, STDOUT_FILENO);
	while (first_op && (first_op->type >= 3 && first_op->type <= 6))
	{
		if (first_op->left && first_op->left->type == CMD)
			break ;
		first_op = first_op->left;
	}
	execute(data, first_op);
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
