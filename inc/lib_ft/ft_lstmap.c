/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:02:52 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/18 23:00:13 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
/*
ft_lstmap()

Iterates the list 'lst' and applies the function f to the content of each node.
Creates a new list resulting of the successive applications of the function f.
The 'del' function is used to delete the content of an element if needed.

Parameters:
	1. t_list *lst: the address of a pointer to an element.
	2. void *(*f)(void *): the address of a function to apply to each element.

Returns the new list. NULL if the allocation fails.
*/

//create a function do duplicate a list
/*statc t_list	*ft_duplist(t_list *lst)
{
    t_list	*new_list;
    t_list	*new_node;

    new_list = NULL;
    while (lst)
    {
        new_node = ft_lstnew(ft_strdup(lst->content));
        if (!new_node)
        {
            ft_lstclear(&new_list, free);
            return (NULL);
        }
        ft_lstadd_back(&new_list, new_node);
        lst = lst->next;
    }
    return (new_list);
} */

/* t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	new_list = ft_duplist(lst);
	if (!new_list)
		return (NULL);
	tmp = new_list;
	while (tmp)
	{
		tmp->content = f(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&lst, del);
	return (new_list);
} */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (new_list);
}

/*static void *ft_do_something(void *content)
{
	// Perform any operation on the content of the node
	// For example, let's convert the content to uppercase
	char *str = (char *)content;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (islower(str[i]))
		{
			str[i] = ft_toupper(str[i]);
		}
	}
	return content;
}*/

/* int main()
{
	// Test 1: Create an empty list
	t_list *list = NULL;
	t_list *result = ft_lstmap(list, ft_do_something, free);
	if (result == NULL)
		printf("Test 1: Passed\n");
	else
		printf("Test 1: Failed\n");

	
	return 0;
} */
