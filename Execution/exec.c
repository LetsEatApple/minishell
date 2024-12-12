/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:38:03 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/12 13:31:14 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(t_node *node, char **env)
{
	if (node->type == PIPE)
		handle_pipe(node, env);
	else if (node->type == REDIR_IN)
		handle_redir_in(node, env);
	else if (node->type == REDIR_OUT)
		handle_redir_out(node, env);
//	else if (node->type == WORD)
		//ft_command(node->value, env); //cmd is an array and needs to be duplicated from cmd
}

int	handle_pipe(t_node *node, char **envp)
{
	int		fd[2];
	pid_t	leftpid;
	pid_t	rightpid;

	if (pipe(fd) == -1)
		print_error("Error making pipe", 1);
	leftpid = fork();
	if (leftpid < 0)
		print_error("Error with fork()\n", 1);
	if (leftpid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_init(node->left, envp);
		exit(EXIT_SUCCESS);
	}
	rightpid = fork();
	if (rightpid < 0)
		print_error("Error with fork()\n", 1);
	if (rightpid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_init(node->right, envp);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(leftpid, NULL, 0);
	waitpid(rightpid, NULL, 0);
	return (0);
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
		printf("bash: %s: Nooo such file or directory\n", node->right->value);
		free(node->right->value);
		exit (EXIT_FAILURE);
	}
	else if (check == 2)
	{
		node->right->value = ft_get_first_word(node->right->value);
		printf("%s:nnv %s: No suchgdg file or directory\n", node->left->value, node->right->value);
		free(node->right->value);
		exit (EXIT_FAILURE);
	}
	return (check);
}

int	handle_redir_in(t_node *node, char **envp)
{
	int	infile;

	while (node->left->type == REDIR_IN)
	{
	// printf("node being opened: '%s'\n", node->right->value);
		infile = open(node->right->value, O_RDONLY);
		if (infile == -1)
		{
			close(infile);
			exit(EXIT_FAILURE);
		}
		node->left = node->left->left;
	}
	infile = open(node->right->value, O_RDONLY);
	if (infile == -1)
	{
		close(infile);
		exit(EXIT_FAILURE);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	ft_init(node->left, envp);
	return (0);
}

int	handle_redir_out(t_node *node, char **envp)
{
	int	outfile;
	int	res;

	res = 0;
	while (node->right->type == REDIR_OUT)
	{
		outfile = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(outfile);
		node->right = node->right->right;
	}
	outfile = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		print_error("Error: Open: File could not be created\n", 1);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	ft_init(node->left, envp);
	return (res);
}
