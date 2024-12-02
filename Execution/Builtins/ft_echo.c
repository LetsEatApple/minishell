/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:20:07 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/02 13:36:21 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    ft_echo(t_data *data)
{
    char    *input;

    input = NULL;
    if (ft_strlen(data->input) == 4)
    {
        printf("\n");
        return (0);
    }
    input = ft_substr(data->input, 5, ft_strlen(data->input) - 5);
    while (*input)
    {
        if (*input == '$')
        {
            print_env_sing(data, input);
            while (*(input + 1))
            {
                if (*(input + 1) == ' ' || *(input + 1)  == '\t' \
                    || *(input + 1) == '\n' || *input == '\f' \
                    || *input == '\v' || *input == '\r')
                    break;
                input++;
            }
        }
        else
            ft_putchar_fd(*input, 1);
        input++;
    }
    printf("\n");
    return (0);
}

int    get_key_len(char *env)
{
    int     i;

    i = 0;
    while (env[i])
    {
        if (env[i] == '=')
            return (i + 1);
        i++;
    }
    return (0);
}

int is_whitespace(char c)
{
    if (!c || c == '\0')
        return (1);
    if (c == ' ' || c == '\t' || c == '\n' \
        || c == '\f' || c == '\v' || c == '\r')
        return (1);
    return (0);
}