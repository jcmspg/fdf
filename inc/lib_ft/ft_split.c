/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:33:58 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/18 19:15:12 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
split()
allocates with malloc and returns an array of strings obtained by splitting 's'
using the character 'c' as a delimiter. The array must be ended by NULL.
s - the string to be split
c - the delimiter character
*/

// count the nbr of words

static size_t	ft_word_count(char const *s, char sep)
{
	size_t	words;

	if (!s)
		return (0);
	words = 0;
	while (*s)
	{
		if (*s == sep)
		{
			while (*s == sep && *s)
				s++;
		}
		else
		{
			while (*s != sep && *s)
				s++;
			words++;
		}
	}
	return (words);
}

static void	word_copying(char **vector, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = i;
			while (s[j] && s[j] != c)
				j++;
			vector[k++] = ft_substr(s, i, j - i);
			i = j;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**words_vector;

	if (s == NULL)
	{
		words_vector = ft_calloc(1, sizeof(char *));
		if (!words_vector)
			return (NULL);
		words_vector[0] = NULL;
		return (words_vector);
	}
	words_vector = ft_calloc(((ft_word_count(s, c)) + 1), sizeof(char *));
	if (!words_vector)
		return (NULL);
	word_copying(words_vector, s, c);
	return (words_vector);
}

/* int main()
{
	char *s = NULL;
	char **words = ft_split(s, ',');
	int i = 0;
	while (words[i])
	{
		printf("%s\n", words[i]);
		i++;
	}
	return 0;
}
 */
