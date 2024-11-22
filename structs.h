/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:17:39 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/21 17:24:44 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_env
// {
//     char    *key;
//     char    *value;
//     struct s_env   *next;
// }   t_env;

typedef struct s_data
{
    char    *input;
    char    **env;
}   t_data;
