/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:54:02 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/18 21:08:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lastadd_back()

adds the node at the end of the list

params
lst - address to a pointer to the first link
new - address to apointer to the node to add

return: none
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
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

	// Print the list
	t_list *current = list;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Free the list
	//ft_lstclear(&list, free);

	return 0;
} */
