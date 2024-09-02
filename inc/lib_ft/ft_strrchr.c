/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:12:27 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/14 16:21:12 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strrch()

used to locate the last occurrence of a character in a string.
It searches fot the specified char and returns pointer to the last occurrence.

as opposed to strchr() it searches from the end of the string to the beginning.
*/

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = ft_strlen(s);
	if (ch == '\0')
		return ((char *)(str + i));
	while (i > 0)
	{
		if (str[i - 1] == ch)
			return ((char *)(str + i - 1));
		i--;
	}
	return (NULL);
}
