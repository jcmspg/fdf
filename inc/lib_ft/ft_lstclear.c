/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:08:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/18 22:36:01 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstclear()

Deletes and frees the given node and every successor of that node,
using the function 'del' and frees the node.
Finally, the pointer to the list must be set to NULL.

Parameters
lst - the address of a pointer to a node
del - the address of the function used to delete the content of the node

Returns
none
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
	return ;
}
/*
void	free_content(void *content)
{
	//free(content);
	(void)content;
}
*/

/*
int main() {
	// Create a linked list with three nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	t_list *node4 = ft_lstnew("Node 4");
	t_list *current = node1;

	// Handle memory allocation error
	if (!node1 || !node2 || !node3 || !node4)
	{
		printf("Error: Unable to create nodes\n");
		return 1;
	}
		// Connect the nodes
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;
	
	while (current != NULL) 
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	node2->next = NULL;
	current = node3;
	// Delete the list
	ft_lstclear(&current, free_content);

	current = node1;
	while (current != NULL) 
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&node1, free_content);
		return 0;
} */
