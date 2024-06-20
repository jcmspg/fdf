/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:21:20 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 18:28:21 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strchr()

returns a pointer to the first occurrence of the character c in the string s.
The terminating null byte is considered part of the string,
so that if c is specified as '\0',
these functions return a pointer to the terminator.
*/
char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return ((char *)(str + i));
		i++;
	}
	if (ch == '\0')
		return ((char *)(str + i));
	return (NULL);
}
