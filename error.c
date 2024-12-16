/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:15:00 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/16 12:34:48 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(t_token **head, char c)
{
	printf("syntax error near unexpected token '%c'\n", c);
	clearlist(head);
	*head = NULL;
}
