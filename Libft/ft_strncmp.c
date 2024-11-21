/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:56:04 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/27 13:22:07 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	if (n == 0)
		return (0);
	x = 0;
	while (s1[x] == s2[x] && s1[x] && x < n - 1)
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	int n = 13;
	char *s1 = "Who do you think you are?";
	char *s2 = "Who do I think I am?";

	printf("%d\n", ft_strncmp(s1, s2, n));
	printf("%d\n", strncmp(s1, s2, n));
	printf("%d\n", ft_strncmp("abcdefgh", "abc\375xx", 5));
	printf("%d\n", strncmp("abcdefgh", "abc\375xx", 5));
}*/
