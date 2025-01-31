/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:39:01 by grmullin          #+#    #+#             */
/*   Updated: 2023/07/05 11:52:51 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	iterate_content(void *content)
{
	// Cast the content to the appropriate type and perform some operation
	int *number = (int *)content;
	(*number)++;
}
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
/*
int	main(void)
{
	// Create a list
	t_list *node1 = (t_list *)malloc(sizeof(t_list));
	if (node1 == NULL)
	{
		printf("Failed to allocate memory for node1.\n");
		return 1;
	}
	int *content1 = (int *)malloc(sizeof(int));
	if (content1 == NULL)
	{
		printf("Failed to allocate memory for content1.\n");
		return 1;
	}
	*content1 = 42;
	node1->content = content1;
	node1->next = NULL;

	t_list *node2 = (t_list *)malloc(sizeof(t_list));
	if (node2 == NULL)
	{
		printf("Failed to allocate memory for node2.\n");
		return 1;
	}
	int *content2 = (int *)malloc(sizeof(int));
	if (content2 == NULL)
	{
		printf("Failed to allocate memory for content2.\n");
		return 1;
	}
	*content2 = 84;
	node2->content = content2;
	node2->next = NULL;

	// Connect the nodes
	node1->next = node2;

	// Call ft_lstiter with the list and the iterate_content function
	ft_lstiter(node1, iterate_content);

	// Check if the content was properly modified
	if (*content1 != 43 || *content2 != 85)
	{
		printf("Content was not iterated properly.\n");
		return 1;
	}

	printf("Content was iterated successfully.\n");
	return 0;
}*/
