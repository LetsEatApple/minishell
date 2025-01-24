/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:16 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/24 17:23:56 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*replace_var(t_data *data, char *var)
{
	char	*val;

	val = NULL;
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

char	*get_var(t_data *data, char *nl, char *var)
{
	char	*tmp;
	char	*tmp2;

	tmp = nl;
	tmp2 = replace_var(data, var);
	nl = ft_strjoin(tmp, tmp2);
	free_ptr(tmp);
	free_ptr(tmp2);
	return (nl);
}

char	*expand_var(t_data *data, char *line)
{
	int		i;
	int		sp;
	char	*nl;

	i = 0;
	sp = i;
	nl = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			nl = save_previous(line, nl, sp, i - sp);
			sp = i +1;
			while (line[sp] && check_seperator(line[sp]) == false)
				sp++;
			nl = get_var(data, nl, ft_substr(line, i, sp - i));
			i = sp;
		}
		else
			i++;
	}
	if (line[sp] != '\0')
		nl = save_previous(line, nl, sp, i - sp);
	return (nl);
}
