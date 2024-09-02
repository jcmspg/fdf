/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:53:44 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/22 15:00:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
calloc()

The calloc() function allocates memory for an array of n memb elements of size
bytes each and returns a pointer to the allocated memory.
The  memory is set to zero.  If nmemb or size is 0,
then calloc() returns either NULL, or a unique pointer value that can later be
successfully passed to free().

*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	total_size = nmemb * size;
	if (nmemb != total_size / size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
