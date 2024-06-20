/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/18 19:12:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstdelone()

Takes as a parameter a node and frees the memory of the node's content using
the function 'del' given as a parameter and free the node.
The memory of 'next' must not be freed

parameters
lst - the node to free
del - the address of the function used to delete the content

returns none
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	if (lst->content != NULL)
		del(lst->content);
	free(lst);
	lst = NULL;
}
/* // Example function to free the content
void free_content(void *content)
{
	//free(content);
	(void)content;
}

int main() {
    // Create a linked list with three nodes
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    if (!node1 || !node2 || !node3) {
        // Handle memory allocation error
        printf("Error: Unable to create nodes\n");
        return 1;
    }

    // Connect the nodes
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;
	
    t_list *current = node1;
	
	while (current != NULL) 
	{
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    // Test ft_lstdelone by deleting node2
    ft_lstdelone(node1, free_content);
	current = node2;
	printf("node1: %s\n", (char *)node1->next);
    // Print the remaining list to verify deletion
    while (current != NULL) {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

    // Clean up: free the remaining nodes and their content
    //ft_lstdelone(node1, free_content); 
    // node3 is already freed when node2 was deleted, so no need to free it again

    return 0;
}
 */
