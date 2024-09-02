/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:41:30 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 19:39:41 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strlcat()

The strlcat() function appends the NUL-terminated string src to the end
     of dst.  It will append at most size - strlen(dst) - 1 bytes,
	 NUL-terminating the result
*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;	
	size_t	total_len;

	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	if (size <= len_d)
		return (len_s + size);
	total_len = len_s + len_d;
	ft_strlcpy(dest + len_d, src, size - len_d);
	return (total_len);
}

/* size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;	
	size_t	total_len;

	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	total_len = len_s + len_d;
	if (size <= len_d)
		return (len_s + size);
	if (total_len < size)
		ft_strlcpy(dest + len_d, src, size - len_d -1);
	else
		ft_strlcpy(dest + len_d, src, 0);
	return (total_len);
*/
/* int main()
{
	char dest[20];
	char const *src;
	size_t total;
	size_t real;

	src = "OLAAAAA";
	total = ft_strlcat(dest, src, 5);
	real = strlcat(dest, src, 3);
	printf("%ld: e o valor de ft_strlcat \n", total);
	//printf("%ld: e o valor de strlcat \n", real);

	return 0;
} */
