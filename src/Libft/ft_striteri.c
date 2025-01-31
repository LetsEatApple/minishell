/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:51:49 by grmullin          #+#    #+#             */
/*   Updated: 2023/06/19 14:32:38 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	ft_add_G(unsigned int i, char *s)
{
	while (s[i])
	{
		s[i] = 'g';
		i++;
	}
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
/*
int	main()
{
	char s[] = "Stringy cheese";
	ft_striteri(s, ft_add_G);

	printf("%s\n", s);
	return (0);
}*/
