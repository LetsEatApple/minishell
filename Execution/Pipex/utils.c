/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:46:24 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/08 11:26:29 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}

void	free_memory(t_pro pipex)
{
	if (pipex.cmd1)
		free_splits(pipex.cmd1);
	if (pipex.cmd2)
		free_splits(pipex.cmd2);
	if (pipex.path)
		free_splits(pipex.path);
}

int	check_string(char *cmd)
{
	int	i;
	int	marker;

	i = 0;
	if (cmd[i] == '\0')
		return (false);
	marker = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			marker++;
		i++;
	}
	if (marker == 0)
		return (false);
	return (true);
}

void	collect_data(t_pro *pipex, char **av, char **env)
{
	int		len;
	char	*path;

	pipex->env = env;
	path = get_path_env(env);
	len = ft_strlen(path) - 5;
	path = ft_substr(path, 5, len);
	pipex->path = ft_split(path, ':');
	free(path);
	if (check_string(av[2]) == true)
	{
		pipex->cmd1 = ft_split(av[2], ' ');
		get_cmd1_path(pipex);
	}
	if (check_string(av[3]) == true)
	{
		pipex->cmd2 = ft_split(av[3], ' ');
		get_cmd2_path(pipex);
	}
}

void	check_files(t_pro *pipex, char **av)
{
	pipex->file1 = av[1];
	pipex->file2 = av[4];
	pipex->fd_in = -1;
	if (access(av[1], F_OK) < 0)
		print_error("no such file or directory: %s\n", av[1]);
	else
	{
		if (access(av[1], R_OK) < 0)
			print_error("permission denied: %s\n", av[1]);
		else
			pipex->fd_in = open(pipex->file1, O_RDONLY);
	}
	pipex->fd_out = open(pipex->file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		print_error("%s: ", strerror(errno));
		print_error("%s\n", pipex->file2);
	}
}
