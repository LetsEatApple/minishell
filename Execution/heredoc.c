/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:46:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/22 13:43:57 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_ptr(void *ptr)
{
	if(ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

/* char	*arr2str(char **arr)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(arr[0]);
		else
		{
			str = ft_strjoin(tmp, arr[i]);
			free_ptr(tmp);
		}
		if (arr[i +1] != 0)
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_ptr(tmp);
		}
		i++;
	}
	free_split(arr);
	return (str);
} */

char	*replace_var(t_data *data, char *var)
{
	char	*val;

	if (ft_strncmp(var, "$", 2) == 0)
		val = ft_strdup("$");
	else if (ft_strncmp("$?", var, 3) == 0)
		val = ft_itoa(g_signal);
	else if (ft_strncmp("$", var, 1) == 0)
	{
		val = search_env(var, data->env);
		if (val == NULL)
			val = ft_strdup("");
	}
	free(var);
	return (val);
}

char	*save_previous(char *line, char *nl, int start, int len)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line, start, len);
	tmp2 = nl;
	nl = ft_strjoin(nl, tmp);
	free(tmp);
	free(tmp2);
	return (nl);
}

char	*expand_var(t_data *data, char *line)
{
	int	i;
	int	sp;
	char	*nl;
	char	*tmp;
	char	*tmp2;

	i = 0;
	sp = i;
	nl = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			nl = save_previous(line, nl, sp, i-sp);
			sp = i +1;
			while (line[sp] && check_seperator(line[sp]) == false)
				sp++;
			tmp = nl;
			tmp2 = replace_var(data, ft_substr(line, i, sp -i));
			nl = ft_strjoin(tmp, tmp2);
			free_ptr(tmp);
			free_ptr(tmp2);
			i = sp;
		}
		else
			i++;
	}
	if (line[sp] != '\0')
		nl = save_previous(line, nl, sp, i-sp);
	return (nl);
}

int	process_line(t_data *data, char **line, t_doc *doc, int *status)
{
	char *tmp;

	if (*line == NULL)
	{
		print_error_fd("warning: here-document delimited by end-of-file (wanted '%s')\n", doc->delimiter, 0);
		*status = false;
		return (false);
	}
	if (ft_strncmp(*line, doc->delimiter, ft_strlen(doc->delimiter) +1) == 0)
		return (false);
	if (check_dollar(*line) == true)
	{
		tmp = *line;
		*line = expand_var(data, *line);
		free(tmp);
	}
	return (true);
}

void	fill_heredoc(t_data *data, t_doc *doc, int *status)
{
	char	*line;

	line = NULL;
	while(1)
	{
		//signal interactive
		line = readline("> ");
		//signal noninteractive
		if (process_line(data, &line, doc, status) == false)
			break ;
		ft_putendl_fd(line, doc->fd);
		free_ptr(line);
	}
	free_ptr(line);
}

int	create_docfile(t_data *data, t_doc *doc)
{
	int	status;

	status = true;
	doc->fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fill_heredoc(data, doc, &status);
	close(doc->fd);
	return (status);
}

void	handler(int sig)
{
	if (sig == SIGINT)
		g_signal = 130;
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

t_node	*get_curr(t_node *node)
{
	while (node->left->type == HEREDOC)
		node = node->left;
	while (node->right->type == HEREDOC)
		node = node->right;
	return (node);
}

void	handle_heredoc(t_data *data, t_node *node)
{
	t_doc	doc;
	t_node	*current;
	int		original_stdin;

	g_signal = 0;
	if (list_size(data->token_list) == 2)
		doc.delimiter = data->token_list->next->value;
	else
		doc.delimiter = node->right->value;
	if (create_docfile(data, &doc) == false)
		return ;
/* 	if (g_signal == 130)
		return ; */
	if (node == NULL)
		return ;
	current = get_curr(node);
	if (!current)
		return ;
	doc.fd = open("temp", O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(doc.fd, STDIN_FILENO) == -1)
	{
		close(doc.fd);
		return ;
	}
	close(doc.fd);
	if (node->left->type == CMD)
		execute(data, node->left);
	else
		execute(data, current->left);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}