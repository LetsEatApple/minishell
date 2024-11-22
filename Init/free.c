/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:21:57 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/22 10:23:44 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_data *data)
{
	int	i;

	free(data->input);
	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
}