/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:37:30 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/25 16:11:21 by grmullin         ###   ########.fr       */
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
