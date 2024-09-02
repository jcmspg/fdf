/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:59:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 16:59:43 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_putchar_fd()

Outputs the character ’c’ to the given file descriptor

write(int fd, const void *buf, size_t count)

fd - file descriptor
*buf (buffer) - data to be written
count - the nbr of bytes to be written from the buffer
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
