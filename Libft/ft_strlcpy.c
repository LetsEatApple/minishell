/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:39:18 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 14:39:22 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (src[i])
		i++;
	if (size != 0)
	{
		j = 0;
		while (src[j] && j < (size - 1))
		{
			dest[j] = src[j];
			j++;
		}
		dest[j] = '\0';
	}
	return (i);
}

// #include <stdio.h>
// #include <bsd/string.h>
// #include <string.h>
// int	main(void)
// {
// 	char dest[] = "Not copied!";
// 	char src[] = "Success!";
// 	char deest[] = "Not copied!";
// 	char srrc[] = "Success!";
// 	printf("%zu\n", ft_strlcpy(dest, src, 3));
// 	printf("%s\n", dest);
// 	printf("%zu\n", strlcpy(deest, srrc, 0));
// 	printf("%s\n", deest);
// 	return (0);
// }
