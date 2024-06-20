/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:57:01 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/16 19:24:41 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lst_add_front()

adds the node 'new' at the beggining of the list

params
lst: the address of a pointer to the first link of a list
new: the address of a pointer to the node to be added tp the list

return : none
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/* int main(void)
{
	// Create a list
	t_list *list = NULL;

	// Create nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Add nodes to the front of the list
	ft_lstadd_front(&list, node1);
	ft_lstadd_front(&list, node2);
	ft_lstadd_front(&list, node3);

	// Print the list
	t_list *current = list;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Free the list
	ft_lstclear(&list, free);

	return 0;
} */
