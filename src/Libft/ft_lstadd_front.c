/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:52:53 by grmullin          #+#    #+#             */
/*   Updated: 2023/07/04 09:20:24 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int	main()
{
	 // Create the head node
    t_list *head = malloc(sizeof(t_list));
    head->content = "Head";
    head->next = NULL;

    // Create a new node
    t_list *newNode = malloc(sizeof(t_list));
    newNode->content = "New Node";
    newNode->next = NULL;

    // Print the list before adding the new node
    printf("List before adding new node:\n");
    t_list *current = head;
    while (current != NULL)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    printf("\n");

    // Add the new node at the front of the list
    ft_lstadd_front(&head, newNode);

    // Print the list after adding the new node
    printf("List after adding new node:\n");
    current = head;
    while (current != NULL)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

    // Free the memory allocated for the nodes
    free(head);
    free(newNode);

    return 0;
}*/
