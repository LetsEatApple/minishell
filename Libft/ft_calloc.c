/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:01:31 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/12 12:48:41 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t arr, size_t size)
{
	size_t	*space;

	space = (void *)malloc(size * arr);
	if (space == NULL)
		return (NULL);
	ft_bzero(space, (size * arr));
	return (space);
}
/*
#include <stdio.h>

int	main()
{
	int	array[] = {1, 2, 3, 4};

	printf("%d\n", (int *)ft_calloc(array, 3));
}*/
