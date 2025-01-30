/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:20:59 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/30 18:12:33 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_line(t_data *data, char **line, char *dm, int *status)
{
	char	*tmp;

	if (*line == NULL)
	{
		ft_putstr_fd("warning: ", 2);
		error_msg("here-document delimited by end-of-file (wanted '%s')\n",
			dm, 0);
		*status = true;
		return (false);
	}
	if (ft_strncmp(*line, dm, ft_strlen(dm) +1) == 0)
	{
		write(data->doc.fd, "\0", 1);
		return (false);
	}
	if (check_dollar(*line) == true)
	{
		tmp = *line;
		*line = expand_var(data, *line);
		free(tmp);
	}
	return (true);
}

void	fill_heredoc(t_data *data, char *dm, int *status)
{
	char	*line;

	line = NULL;
	while (1)
	{
		set_sig_interactive();
		line = readline("> ");
		set_sig_noninteractive();
		if (process_line(data, &line, dm, status) == false)
			break ;
		ft_putendl_fd(line, data->doc.fd);
		free_ptr(line);
	}
	free_ptr(line);
	
}

int	create_docfile(t_data *data, char *dm)
{
	int			status;
	char		*tmp;
	static int	num;

	if (data->doc.file)
	{
		if (access(data->doc.file, F_OK) == 0)
			unlink(data->doc.file);
		free(data->doc.file);
		data->doc.file = NULL;
	}
	tmp = ft_itoa(num);
	data->doc.file = ft_strjoin("temp", tmp);
	{
		free(tmp);
		num++;
	}
	status = true;
	data->doc.fd = open(data->doc.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fill_heredoc(data, dm, &status);
	close(data->doc.fd);
	return (status);
}

/* void	create_docfile(t_data *data, char *key)
{
	int		doc;
	char	buffer[100];
	int		i;
	char	*history;

	doc = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	history = data->input;
	data->input = ft_strjoin(data->input, "\n");
	free(history);
	while (1)
	{

		write(STDIN_FILENO,"> ", 3);
		i = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (i == -1)
		{
			if (errno == EINTR)
			{
				if( g_signal == 130)
					break ;
			}
			else
			{
				perror("Error reading input");
				return ;
			}
		}
		else
		{
			buffer[i] = '\0';
			history = data->input;
			data->input = ft_strjoin(history, buffer);
			free(history);
			if(ft_strncmp(key, buffer, ft_strlen(key)) == 0)
				break ;
			if (buffer[0] == '\0')
				write (doc, "\n", 1);
			write(doc, buffer, i);
		}
	}
	close(doc);
} */