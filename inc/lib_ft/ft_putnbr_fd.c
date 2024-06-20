/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:54:15 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 17:00:15 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_putnbr_fd()

Outputs the integer ’n’ to the given file descriptor.
*/

void	ft_putnbr_fd(int n, int fd)
{
	long	long_nb;

	long_nb = (long)n;
	if (long_nb < 0)
	{
		ft_putchar_fd('-', fd);
		long_nb = -long_nb;
	}
	if (long_nb >= 10)
	{
		ft_putnbr_fd((long_nb / 10), fd);
	}
	ft_putchar_fd(('0' + long_nb % 10), fd);
}
