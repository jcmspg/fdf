/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/17 16:07:32 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstlast()

returns the last node of the list

params
lst - the beggining of the list

returns 
the last node
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

/* int main(void)
{
	t_list *list = NULL;
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	ft_lstadd_back(&list, node3);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node1);
	ft_lstadd_front(&list, node1);
	ft_lstadd_front(&list, node2);
	ft_lstadd_front(&list, node3);

	// Print the list
	printf("Last node: %s\n", (char *)ft_lstlast(list)->content);

	// Free the list
	//ft_lstclear(&list, free);

	return 0;
} */
