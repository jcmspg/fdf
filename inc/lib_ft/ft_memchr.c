/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:04:19 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/23 23:26:00 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memchr()

locates the first occurrence of c (converted to an unsigned
char) in string s.

used to search for a specific byte within a block of memory.
It takes three arguments: a pointer to the memory block (*s),
the value to search for (as an integer) (c),
and the number of bytes to search within (n).
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
			return (str + i);
		i++;
	}
	return (NULL);
}
