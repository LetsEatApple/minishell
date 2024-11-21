/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:36:43 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/25 21:04:23 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_to_char(char *str, unsigned int n, long int len)
{
	while (n > 0)
	{
		str[len--] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		len;
	int				sign;
	unsigned int	number;

	len = ft_len(n);
	sign = 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		sign = sign * -1;
		number = n * -1;
		str[0] = '-';
	}
	else
		number = n;
	str = ft_to_char(str, number, len);
	return (str);
}
/*
#include <stdio.h>

int	main()
{
	printf("%s\n", ft_itoa(638));
	printf("%s\n", ft_itoa(-2147483648));
}*/
