/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:32:36 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/25 21:05:02 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char	*p;
	unsigned char	x;

	p = (unsigned char *)s;
	x = (unsigned char)c;
	while (n > 0)
	{
		if (*p == x)
			return (p);
		p++;
		n--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str = "abcdef";
	int d = 'd';

	printf("%s\n", (char *)ft_memchr(str, d, 5));
	printf("%s\n", (char *)memchr(str, d, 5));
}*/
