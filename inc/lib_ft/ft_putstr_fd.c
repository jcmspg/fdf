/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:44:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 17:00:50 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_putstr_fd()

Outputs the string ’s’ to the given file descriptor

write(int fd, const void *buf, size_t count)
fd - file descriptor
*buf (buffer) - data to be written
count - the nbr of bytes to be written from the buffer
*/

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
