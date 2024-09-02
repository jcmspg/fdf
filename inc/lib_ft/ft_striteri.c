/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:44:36 by joao              #+#    #+#             */
/*   Updated: 2024/04/18 14:29:23 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
striteri()

Applies the function ’f’ on each character of the string passed as argument,
passing its index as first argument. Each character is passed by
address to ’f’ to be modified if necessary

Parameters:
	#1. The string on which to iterate.
	#2. The function to apply to each character.

Return value: None.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (*s)
	{
		f(i, s);
		i++;
		s++;
	}
}
// testing the function

/* static void modify_char(unsigned int index, char *c) {
    // Increment the ASCII value of the character by the index
    *c = ft_toupper(*c);
}

int main() {
    char str[] = "oye, como va? mi ritmo bueno pa' gozar, mulata!";
    printf("Original string: %s\n", str);
    ft_striteri(str, modify_char);
    printf("Modified string: %s\n", str);
    return 0;
} */
