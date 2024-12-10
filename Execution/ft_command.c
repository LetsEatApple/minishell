/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/10 15:35:46 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(t_data *data)
{
	if (is_built_in(data->input)) // data->
		ft_built_ins(data);
    // else if (ft_exec_command(node, envp) == 0)
    //     return (0);
	else
	{
		printf("%s: command not found\n", data->input);
		g_signal = 127;
	}
	g_signal = 0;
}
