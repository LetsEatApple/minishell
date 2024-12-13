/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:38:03 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/13 13:43:20 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_node *node, char **env)
{
	// if (node->type != CMD)
	// 	printf("Init w/ '%s', Type: %s\n", node->value, get_token_type(node->type));
	if (node->type == PIPE)
		handle_pipe(node, env);
	else if (node->type == REDIR_IN)
		handle_redir_in(node, env);
	else if (node->type == REDIR_OUT)
		handle_redir_out(node, env);
	else if (node->type == CMD)
		ft_command(node->cmd, env);
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
		execute(node->left, envp);
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
		execute(node->right, envp);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(leftpid, NULL, 0);
	waitpid(rightpid, NULL, 0);
	return (0);
}

int	handle_redir_in(t_node *node, char **envp)
{
	t_node	*current;
	char	*final_file;
	int		original_stdin;
	int		infile;

	current = node;
	final_file = NULL;
	while (current->left && current->left->type == REDIR_IN)
		current = current->left;
	if (current->right && current->right->value)
		final_file = current->right->value;
	if (!final_file)
		return (1);
	infile = open(final_file, O_RDONLY);
	if (infile == -1)
	{
		perror("Error opening input file");
		return (1);
	}
	original_stdin = dup(STDIN_FILENO);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		return (1);
	}
	close(infile);
	execute(node->left, envp);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
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
	execute(node->left, envp);
	return (res);
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
