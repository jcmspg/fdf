/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:40:16 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/14 17:38:58 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	uc1;
	unsigned char	uc2;

	while ((n > 0) && (*s1 == *s2) && (*s1 != '\0'))
	{
		s2++;
		s1++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	uc1 = (unsigned char)*s1;
	uc2 = (unsigned char)*s2;
	return (uc1 - uc2);
}
