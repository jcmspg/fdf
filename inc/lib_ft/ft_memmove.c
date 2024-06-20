/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:51 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 16:50:30 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memmove()

The memmove() function copies n bytes from memory area src to memory area dest.
The memory areas may overlap.
Returns pointer to dest.
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	size_t		i;
	char		*d;

	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
