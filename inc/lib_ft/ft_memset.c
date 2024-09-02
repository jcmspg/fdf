/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:40:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 20:05:07 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memset()

The memmset() function fills the first n bytes of the memory area pointed to
by s with the constant byte c.
Returns pointer to s.
*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	ch;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		str[i] = ch;
		i++;
	}
	return (s);
}
