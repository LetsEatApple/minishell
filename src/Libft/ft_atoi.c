/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:23:40 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/27 15:06:49 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	x;
	int	sign;
	int	result;

	x = 0;
	sign = 1;
	result = 0;
	while (str[x] == ' ' || (str[x] >= 9 && str[x] <= 13))
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			sign = -sign;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		result = result * 10 + (str[x] - 48);
		x++;
	}
	return (result * sign);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main()
{
	printf("%d\n", ft_atoi("---+--+2147483646"));
	printf("%d\n", ft_atoi("  	+++---4352959...99s"));
	printf("%d\n", ft_atoi("\n\n+2345245??"));
	printf("%d\n", ft_atoi("  12321499"));
	printf("%d\n\n", ft_atoi("-+48"));
	
	printf("%d\n", atoi("---+--+2147483646"));
	printf("%d\n", atoi("  	+++---4352959...99s"));
	printf("%d\n", atoi("\n\n+2345245??"));
	printf("%d\n", atoi("  12321499"));
	printf("%d\n\n", atoi("-+48"));
}*/
