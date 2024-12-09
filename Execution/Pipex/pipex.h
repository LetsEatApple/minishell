/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:21:39 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/08 11:08:27 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_pro
{
	char	*file1;
	char	*file2;
	int		fd_in;
	int		fd_out;
	int		fd;
	char	**cmd1;
	int		cmd1_size;
	char	**cmd2;
	int		cmd2_size;
	char	**env;
	char	**path;
	char	*cmd_path1;
	char	*cmd_path2;
}	t_pro;

void	collect_data(t_pro *pipex, char **av, char **env);
void	free_splits(char **splits);
void	free_memory(t_pro pipex);
int		cmd1(t_pro *pipex);
int		cmd2(t_pro *pipex);
char	*get_path_env(char **env);
char	*check_path(t_pro *pipex, int cmd);
t_pro	get_parameters(t_pro pipex, int cmd);
void	ft_pipe(t_pro *pipex);
void	get_cmd1_path(t_pro *pipex);
void	get_cmd2_path(t_pro *pipex);
void	error_exit(t_pro *pipex, int fd);
void	redirect_close_cmd1(t_pro *pipex, int pfd1, int pfd0);
void	redirect_close_cmd2(t_pro *pipex, int pfd1, int pfd0);
void	write_to_outfile(t_pro *pipex, int pfd);
int		check_string(char *cmd);
void	check_files(t_pro *pipex, char **av);
void	print_error(const char *error, char *target);
void	error_close(int fd);

#endif