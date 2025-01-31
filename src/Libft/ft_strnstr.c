/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:12:20 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/28 11:57:03 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, int n)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[x] && x <= (unsigned int)n)
	{
		if (haystack[x] == needle[y])
		{
			while (haystack[x + y] == needle[y] && haystack[x + y]
				&& x + y < (unsigned int)n)
			{
				if (needle[y + 1] == '\0')
					return ((char *)haystack + x);
				y++;
			}
			y = 0;
		}
		x++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main()
{
	char hay[] = "On a sunny afternoon";
	char needle[] = "sunny";
	int n = -1;

	printf("%s\n", ft_strnstr(hay, needle, n));
	printf("%s\n", strnstr(hay, needle, n));
}*/
