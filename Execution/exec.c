/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:38:03 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/05 22:30:22 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_data *data, t_node *node)
{
	// if (node->type != CMD)
	// 	ft_printf_fd(node->value);
	if (node->type == PIPE)
		handle_pipe(data, node);
	else if (node->type == REDIR_IN)
		handle_redir_in(data, node);
	else if (node->type == REDIR_OUT)
		handle_redir_out(data, node);
	else if (node->type == REDIR_OUT_APPEND)
		handle_redir_append(data, node);
	else if (node->type == CMD)
		ft_command(data, node->cmd);
}

void	handle_pipe(t_data *data, t_node *node)
{
	int		fd[2];
	pid_t	leftpid;
	pid_t	rightpid;

	if (pipe(fd) == -1)
		printf_error("Error making pipe", 1);
	leftpid = fork();
	if (leftpid < 0)
		printf_error("Error with fork()\n", 1);
	if (leftpid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(data, node->left);
		exit(EXIT_SUCCESS);
	}
	rightpid = fork();
	if (rightpid < 0)
		printf_error("Error with fork()\n", 1);
	if (rightpid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute(data, node->right);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(leftpid, NULL, 0);
	waitpid(rightpid, NULL, 0);
}

int	ft_wait(int pid1, t_node *node)
{
	int	status1;
	int	check;

	status1 = 0;
	check = 0;
	waitpid(pid1, &status1, WUNTRACED);
	if (WIFEXITED(status1))
		check = WEXITSTATUS(status1);
	if (check == 1) // all of this sep. ft
	{
		node->right->value = ft_get_first_word(node->right->value);
		printf("%s: No such file or directory\n", node->right->value);
		free(node->right->value);
		exit (EXIT_FAILURE);
	}
	else if (check == 2)
	{
		node->right->value = ft_get_first_word(node->right->value);
		printf("%s:nnv %s: No such file or directory\n", node->left->value, node->right->value);
		free(node->right->value);
		exit (EXIT_FAILURE);
	}
	return (check);
}
