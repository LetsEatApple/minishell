/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:54:20 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/08 11:09:20 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	ft_pipe(t_pro *pipex)
{
	pipex->fd = -1;
	if (pipex->fd_in != -1 && pipex->cmd1 != NULL)
	{
		cmd1(pipex);
		close(pipex->fd_in);
	}
	if (pipex->fd_in != -1 && pipex->cmd1 == NULL)
		error_close(pipex->fd_in);
	if (pipex->fd == -1)
		pipex->fd = open("/dev/null", O_RDONLY);
	if (pipex->fd == -1)
	{
		perror("Error opening File '/dev/null'");
		error_exit(pipex, pipex->fd_out);
	}
	if (pipex->fd_out != -1 && pipex->cmd2 != NULL)
	{
		cmd2(pipex);
		close(pipex->fd_out);
	}
	if (pipex->fd_out != -1 && pipex->cmd2 == NULL)
		error_close(pipex->fd_out);
	if (pipex->fd != -1)
		close(pipex->fd);
}

void	print_error(const char *error, char *target)
{
	int		i;

	i = 0;
	while (error[i])
	{
		if (error[i] == '%')
		{
			i++;
			ft_putstr_fd(target, 2);
		}
		else
			ft_putchar_fd(error[i], 2);
		i++;
	}
}

int	cmd1(t_pro *pipex)
{
	int	pfd[2];
	int	id;

	if (pipe(pfd) == -1)
		return (2);
	id = fork();
	if (id < 0)
		return (3);
	if (id == 0)
	{
		redirect_close_cmd1(pipex, pfd[1], pfd[0]);
		if (execve(pipex->cmd1[0], pipex->cmd1, pipex->env) == -1)
			print_error("command not found: %s\n", pipex->cmd1[0]);
		free_memory(*pipex);
		exit (4);
	}
	wait(NULL);
	close(pfd[1]);
	pipex->fd = dup(pfd[0]);
	close(pfd[0]);
	return (0);
}

int	cmd2(t_pro *pipex)
{
	int		pfd[2];
	int		id;

	if (pipe(pfd) == -1)
		return (5);
	id = fork();
	if (id < 0)
		return (6);
	if (id == 0)
	{
		redirect_close_cmd2(pipex, pfd[1], pfd[0]);
		execve(pipex->cmd2[0], pipex->cmd2, pipex->env);
		print_error("command not found: %s\n", pipex->cmd2[0]);
		free_memory(*pipex);
		exit (7);
	}
	wait(NULL);
	close(pfd[1]);
	write_to_outfile(pipex, pfd[0]);
	close(pipex->fd_out);
	close(pfd[0]);
	return (0);
}
