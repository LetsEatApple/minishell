/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:24:24 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/23 18:37:21 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	int a = 52;
	int b = 105;
	int c = 127;
	int	d = 8;

	ft_isprint(a);
	ft_isprint(b);
	ft_isprint(c);
	ft_isprint(d);
}*/
