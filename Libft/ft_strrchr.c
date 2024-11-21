/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:55:22 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/27 12:04:59 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	d;

	d = ft_strlen(str);
	while (d >= 0)
	{
		if (str[d] == (char)c)
			return (&str[d++]);
		d--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	int c = 'g';
	char *str = "String me up grassy";

	printf("%s\n", ft_strrchr(str, c));
	printf("%s\n", strrchr(str, c));
}*/
