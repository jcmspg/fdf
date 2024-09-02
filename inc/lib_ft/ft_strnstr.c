/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:44:29 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/15 17:00:40 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	j = 0;
	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while ((big[i] != '\0') && (i < len))
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
