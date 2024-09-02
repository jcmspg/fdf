/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:09:04 by joao              #+#    #+#             */
/*   Updated: 2024/04/12 17:47:21 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strmapi()

apply the function f to each character of the string passed as argument by
giving its index as first argument to create a new string resulting
from the successive applications of f.

Parameters:
	#1. The string on which to iterate.
	#2. The function to apply to each character.

Return value: The string created from the successive applications of f.

	// checking if the string and the function are valid
	// getting the length of the string
	// allocating memory for the new string
	// looping through the string and applying the function to each character
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	str = malloc((sizeof (char)) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[len] = '\0';
	return (str);
}
/* // testing the function

// Wrapper function for ft_toupper
static char ft_toupper_wrapper(unsigned int index, char c)
{
    // Call ft_toupper with the character c
    return ft_toupper(c);
}

int main()
{
    char input[] = "oye como va, mi ritmo bueno pa' gozar, mulata";
    char *output = ft_strmapi(input, &ft_toupper_wrapper);
    printf("%s\n", output); // Output: "Hfnos"
    free(output); // Free the allocated memory
    return 0;
} */
