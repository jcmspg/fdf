/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:25:27 by malourei          #+#    #+#             */
/*   Updated: 2024/06/23 00:38:38 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlenn(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	if (!src)
	{
		*dest = 0;
		return ;
	}
	i = 0;
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strncat(char *dest, char *src, int size)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlenn(dest);
	while (size > 0)
	{
		dest[n + i] = src[i];
		i++;
		size--;
	}
	dest[n + i] = '\0';
}
