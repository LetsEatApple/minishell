/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:12:13 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/08 11:08:10 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_close(int fd)
{
	ft_putstr_fd("command not found: \n", 2);
	close (fd);
}

void	error_exit(t_pro *pipex, int fd)
{
	close(fd);
	free_memory(*pipex);
	exit (4);
}

void	redirect_close_cmd1(t_pro *pipex, int pfd1, int pfd0)
{
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	close(pfd0);
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		error_exit(pipex, pipex->fd_in);
	close(pipex->fd_in);
	if (dup2(pfd1, STDOUT_FILENO) == -1)
		error_exit(pipex, pfd1);
	close(pfd1);
}

void	redirect_close_cmd2(t_pro *pipex, int pfd1, int pfd0)
{
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	close(pfd0);
	if (dup2(pipex->fd, STDIN_FILENO) == -1)
		error_exit(pipex, pipex->fd);
	close(pipex->fd);
	if (dup2(pfd1, STDOUT_FILENO) == -1)
		error_exit(pipex, pfd1);
	close(pfd1);
}

void	write_to_outfile(t_pro *pipex, int pfd)
{
	int		i;
	char	*res;

	i = 1;
	while (i > 0)
	{
		i = read(pfd, &res, 1);
		if (i == -1 || i == 0)
			break ;
		write(pipex->fd_out, &res, 1);
	}
}
