/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:36:09 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/17 18:41:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstiter()

Iterates through 'lst' and applies the function 'f' to the content of each node

Parameters
lst - the address of a pointer to a node
f - the address of the function used to iterate on the content

Returns
none

*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}
