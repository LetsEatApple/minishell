/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:05:32 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/23 18:24:55 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	int a = 52;
	int b = 105;
	int c = 93;
	int	d = 8;

	ft_isalpha(a);
	ft_isalpha(b);
	ft_isalpha(c);
	ft_isalpha(d);
}*/
