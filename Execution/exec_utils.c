/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:44:35 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/17 17:04:18 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_printf_fd(char *print)
{
	char	*final;
	char	*bash;

	bash = ft_strjoin("bash: ", print);
	final = ft_strjoin(bash, ": No such file or directory\n");
	ft_putstr_fd(final, 2);
	free(bash);
	free(final);
}
void	print_error(char *str, int n)
{
	printf("%s\n", str);
	g_signal = n;
}
