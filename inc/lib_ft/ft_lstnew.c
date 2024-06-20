/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:14:18 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/18 22:36:00 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstnew()

allocates and returns a new node.
the 'content' is initialized with the value of its parameter.
the 'next' is initialized to NULL

content - content to create the node with

return - the new node
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/* int main(int argc, char *argv[])
{
	t_list	*node;
	void	*content;

	if (argc != 2)
		return (0);
	else
	{
		content = argv[1];
		node = ft_lstnew(content);
		printf("content is: %s \n", (char *)node->content);
		printf("next is: %p\n", (void *)node->next);
		free(node);
		return (0);
	}
}
 */
