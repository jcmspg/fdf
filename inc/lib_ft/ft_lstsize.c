/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:41:44 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/17 16:05:22 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstsize()

counts the number of nodes in a list

param
lst - the beggining of the list

returns
the length of the list
*/

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		i;

	i = 0;
	if (lst == NULL)
		return (0);
	else
	{
		current = lst;
		while (current != NULL)
		{
			current = current->next;
			i++;
		}
		return (i);
	}
}

/* int main()
{
	t_list *list = NULL;
	int	i = 0;

	// Create nodes and add them to the list
	while(i <= 5)
	{
		t_list *new_node = ft_lstnew("Node");
		ft_lstadd_back(&list, new_node);
		printf("Size of the list after adding node %d: %d\n", i, ft_lstsize(list));
		i++;
	}
	return (0);
} */
