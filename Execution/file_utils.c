/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:09:24 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/26 20:19:16 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_infile_validity(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		g_signal = 1;
		return (NULL);
	}
	close(fd);
	return (file);
}

char	*check_outfile_validity(char *file, t_token_type type)
{
	int	fd;

	// ft_putstr_fd("testing: ", 2);
	// ft_putstr_fd(file, 2);
	// ft_putstr_fd("\n", 2);
	if (type == REDIR_OUT)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(file);
			g_signal = 1;
			return (NULL);
		}
		close(fd);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(file);
			g_signal = 1;
			return (NULL);
		}
		close(fd);
	}
	return (file);
}