/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:05:12 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/27 13:54:46 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	sub_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	sub_len = 0;
	if ((size_t)start + len <= ft_strlen(s))
		sub_len = len;
	else if ((size_t)start > ft_strlen(s))
		sub_len = 0;
	else if ((size_t)start + len >= ft_strlen(s))
		sub_len = ft_strlen(s) - start;
	sub = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
/*
#include <stdio.h>

int	main()
{
	char	big[] = "tripouille";
	unsigned int i = 8;
	char *s = ft_substr(big, i, 42000);

	printf("%s\n", s);
	free(s);
}*/
