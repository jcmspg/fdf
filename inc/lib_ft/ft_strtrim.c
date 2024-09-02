/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:06:03 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/18 20:04:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strtrim()

Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
specified in ’set’ removed from the beginning and the end of the string.

Returns the trimmed string, or NULL if the allocation fails.
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strrchr(set, s1[len - 1]))
		len--;
	if (len < i)
		i = len;
	new_str = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[j] = s1[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}
/* int main() {
	char *s1 = "   hello world   ";
	char *set = " ";
	char *trimmed = ft_strtrim(s1, set);
	
	printf("Original string: \"%s\"\n", s1);
	printf("Trimmed string: \"%s\"\n", trimmed);
	
	free(trimmed);
	
	return 0;
} */
