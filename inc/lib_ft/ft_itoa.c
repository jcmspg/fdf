/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:25:38 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/15 18:23:00 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
itoa()

Allocates (with malloc(3)) and returns a string representing
the integer received as an argument. Negative numbers must be handled

Returns the string representing the integer.
NULL if the allocation fails.
*/

// 1 calculate the length of the number

static size_t	ft_nbrlen(long n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	char	*s;
	long	nbr;

	nbr = (long)n;
	len = ft_nbrlen(nbr);
	i = 0;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (nbr < 0)
	{
		s[0] = '-';
		nbr *= -1;
		i++;
	}
	while (len > i)
	{
		len--;
		s[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (s);
}

/* int main()
{
	int n1 = 2147483647;
	char *s1 = ft_itoa(n1);
	int n2 = -2147483648;
	char *s2 = ft_itoa(n2);
	printf("%s\n", s1);
	printf("%s\n", s2);
	free(s1);
	free(s2);
	return 0;
} */
