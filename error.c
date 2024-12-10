/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:15:00 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 15:25:49 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(t_token **head, char c)
{
	printf("syntax error near unexpected token '%c'\n", c);
	clearlist(head);
	*head = NULL;
}
