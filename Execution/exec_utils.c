/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:44:35 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/28 17:56:00 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_infile(t_data *data, t_node *red_out)
{
	t_node	*node;
	char	*infile;

	node = red_out;
	if (data->pipes == 0 && node->right->type == 4)
	{
		if (data->red_in > 0 && data->infile == 0)
		{
			while (node->type != REDIR_IN)
				node = node->right;
		}
		infile = get_infile_red_in(data, node);
		data->infile = 1;
		if (!infile)
		{
			dup2(data->std_out_fd, STDOUT_FILENO);
			return (1);
		}
		execute(data, node);
	}
	return (0);
}

char	*ft_get_first_word(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == ' ')
			break ;
		i++;
	}
	new = malloc(sizeof(char) * i);
	j = 0;
	while (j <= i)
	{
		new[j] = s[j];
		j++;
	}
	return (new);
}
