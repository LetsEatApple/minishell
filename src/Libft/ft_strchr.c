/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:56:54 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/08 12:37:36 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	d;

	d = 0;
	while (d <= ft_strlen(str))
	{
		if (str[d] == (char)c)
			return ((char *)&str[d++]);
		d++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	int c = 'g';
	char str[] = "String me up";

	printf("%s\n", ft_strchr(str, c));
	printf("%s\n", strchr(str, c));
	printf("%s\n", ft_strchr("teste", 'e' + 256));
	printf("%s\n", strchr("teste", 'e' + 256));
	printf("%s\n", ft_strchr("teste", 1024));
	printf("%s\n", strchr("teste", 1024));
	printf("%c\n", 1024);
	printf("%c\n", 1024);
}*/
