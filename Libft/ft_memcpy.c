/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:16:19 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/26 12:59:35 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, int n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == 0 && src == 0)
		return (NULL);
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>

int main()
{
	char dest[] = "Destination";
	char src[] = "Go go go!";

	printf("%s\n", (unsigned char *)ft_memcpy(dest, src, 8));
	printf("%s\n", (unsigned char *)memcpy(dest, src, 8));
}*/
