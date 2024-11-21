/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:08:04 by grmullin          #+#    #+#             */
/*   Updated: 2023/07/04 11:03:45 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*n;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			n = ft_lstlast(*lst);
			n->next = new;
		}
	}
}
/*
int main()
{
    // Create an empty list
    t_list *head = NULL;

    // Test with an empty list
    printf("Empty List: ");
    if (!head)
        printf("List is empty.\n");

    // Create nodes
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    t_list *node3 = malloc(sizeof(t_list));

    node1->content = "Node 1";
    node1->next = NULL;
    node2->content = "Node 2";
    node2->next = NULL;
    node3->content = "Node 3";
    node3->next = NULL;

    // Add nodes to the list
    ft_lstadd_back(&head, node1);
    ft_lstadd_back(&head, node2);
    ft_lstadd_back(&head, node3);

    // Print the list
    printf("List after adding nodes: ");
    t_list *current = head;
    while (current)
    {
        printf("%s ", (char *)current->content);
        current = current->next;
    }
    printf("\n");

    // Free the memory allocated for the nodes
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/
