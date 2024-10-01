/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:15:50 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 20:26:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_char_to_value(char c, const char *base_str)
{
	int	i;

	i = 0;
	while (base_str[i] != '\0')
	{
		if (base_str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_base_length(const char *base_str)
{
	int	base;

	base = 0;
	while (base_str[base] != '\0')
		base++;
	return (base);
}

void	skip_whitespace_and_sign(const char *str, int *i, int *sign)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	calculate_result(const char *str, const char *base_str, int base, int *i)
{
	int	res;
	int	value;

	res = 0;
	while (1)
	{
		value = ft_char_to_value(str[*i], base_str);
		if (value == -1)
			break ;
		res = res * base + value;
		(*i)++;
	}
	return (res);
}

int	ft_atoi_base(const char *str, const char *base_str)
{
	int	i;
	int	res;
	int	sign;
	int	base;

	i = 0;
	sign = 1;
	base = get_base_length(base_str);
	skip_whitespace_and_sign(str, &i, &sign);
	res = calculate_result(str, base_str, base, &i);
	return (res * sign);
}
