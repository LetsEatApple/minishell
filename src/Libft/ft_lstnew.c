/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:29:51 by grmullin          #+#    #+#             */
/*   Updated: 2023/07/05 13:53:49 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
int	main()
{
	int data = 42;
    t_list *node = ft_lstnew(&data);
    
    if (node != NULL)
	{
        printf("Content: %d\n", *(int *)(node->content));
        printf("Next: %p\n", node->next);
    }
	else
	{
        printf("Error creating the new node.\n");
    }

    return 0;
}*/
