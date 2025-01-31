/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:57:51 by grmullin          #+#    #+#             */
/*   Updated: 2023/11/28 09:58:35 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*cat;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	cat = (char *)malloc(sizeof(char) * len);
	if (cat == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		cat[i++] = s2[j++];
	cat[i] = '\0';
	return (cat);
}
/*
#include <stdio.h>

int	main()
{
	const char str[] = "Chilli sin";
	const char str1[] = " carne";

	printf("%s\n", ft_strjoin(str, str1));
}*/
