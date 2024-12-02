/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/27 15:22:42 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_command(t_data *data)
{
    if (is_built_in(data->input))
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
