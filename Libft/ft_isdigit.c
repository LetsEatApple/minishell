/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:25:43 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/23 18:26:17 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}
/*
int	main()
{
	int a = '3';
	int b = 'b';
	int c = ')';
	int	d = '\b';

	ft_isdigit(a);
	ft_isdigit(b);
	ft_isdigit(c);
	ft_isdigit(d);
}*/
