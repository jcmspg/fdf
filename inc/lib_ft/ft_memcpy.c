/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:23:48 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 16:50:00 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memcpy()

The memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap.
Returns pointer to dest.
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	size_t		i;
	char		*d;

	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
