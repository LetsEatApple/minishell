/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:47:57 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/27 10:41:25 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	d;
	size_t	s;

	src_len = ft_strlen(src);
	if (!dest && size == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	d = dest_len;
	if (size <= d)
		return (size + src_len);
	s = 0;
	while (src[s] && d + 1 < size)
	{
		dest[d] = src[s];
		d++;
		s++;
	}
	dest[d] = '\0';
	return (dest_len + src_len);
}
/*
#include <bsd/string.h>

int	main()
{
	char *str = "the cake is a lie !\0I'm hidden lol\r\n";
	char buff1[0xF00] = "there is no stars in the sky";
	char buff2[0xF00] = "there is no stars in the sky";
	size_t max = strlen("the cake is a lie !\0I'm hidden lol\r\n")
	 + strlen("there is no stars in the sky");

	printf("%zu\n", ft_strlcat(buff1, str, max));
	printf("%zu\n", strlcat(buff2, str, max));
	printf("%s\n", buff1);
	printf("%s\n", buff2);
}*/
