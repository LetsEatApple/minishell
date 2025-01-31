/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:42:04 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/25 21:07:12 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, int n)
{
	unsigned char	*p;
	unsigned char	x;

	p = (unsigned char *)s;
	x = (unsigned char)c;
	while (n > 0)
	{
		*p = x;
		p++;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char str[] = "alohaaaaa";
	int c = 'j';

	printf("%s\n", (char *)ft_memset(str, c, 3));
	printf("%s\n", (char *)memset(str, c, 3));
}*/
