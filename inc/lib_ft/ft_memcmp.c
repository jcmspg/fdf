/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:13:22 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 16:48:16 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
memcmp()

function compares byte string s1 against byte string s2.
Both strings are assumed to be n bytes long.

it compares the the contents of the two memory blocks starting from the
specified mememory addresses up to a certain number of bytes.

this function is often used to compare arrays, strings,
or any other data structure.

s1 s2 points to mem blocks
returns 0 if mem is equal
		-value if s1<s2
		+value if s1>s2
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
