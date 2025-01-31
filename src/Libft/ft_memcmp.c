/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:11:11 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/26 20:55:41 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (i < n && p1[i] == p2[i])
		i++;
	if (i == n)
		return (0);
	else
		return (p1[i] - p2[i]);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str1 = "\xff\xaa\xde\x12";
	char *str2 = "\xff\xaa\xde\x12MACOSAAAAA";

	printf("%d\n", ft_memcmp(str1, str2, 7));
	printf("%d\n", memcmp(str1, str2, 7));
}*/
