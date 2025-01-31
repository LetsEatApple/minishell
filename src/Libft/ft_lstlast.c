/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:46 by grmullin          #+#    #+#             */
/*   Updated: 2023/07/04 10:06:40 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}
/*
int main()
{
    // Create an empty list
    t_list *head = NULL;

    // Test with an empty list
    t_list *lastNode = ft_lstlast(head);
    if (lastNode == NULL)
        printf("List is empty.\n");
    else
        printf("Last node content: %p\n", lastNode->content);

    // Create a list with three nodes
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    t_list *node3 = malloc(sizeof(t_list));

    node1->content = "Node 1";
    node1->next = node2;
    node2->content = "Node 2";
    node2->next = node3;
    node3->content = "Node 3";
    node3->next = NULL;

    // Test with a non-empty list
    lastNode = ft_lstlast(node1);
    printf("Last node content: %s\n", (char *)lastNode->content);

    // Free the memory allocated for the nodes
    free(node1);
    free(node2);
    free(node3);
}*/
