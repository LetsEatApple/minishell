/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:02:45 by grmullin          #+#    #+#             */
/*   Updated: 2023/07/03 21:19:32 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int main()
{
    // Create an empty list
    t_list *head = NULL;

    // Test with an empty list
    int size = ft_lstsize(head);
    printf("Size of the empty list: %d\n", size);

    // Create a list with three nodes
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    t_list *node3 = malloc(sizeof(t_list));

    node1->content = NULL;
    node1->next = node2;
    node2->content = NULL;
    node2->next = node3;
    node3->content = NULL;
    node3->next = NULL;

    // Test with a non-empty list
    size = ft_lstsize(node1);
    printf("Size of the list with three nodes: %d\n", size);

    // Free the memory allocated for the nodes
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/
