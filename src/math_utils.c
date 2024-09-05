/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:54:07 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/05 20:42:23 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float ft_fabs(float n)
{
    if (n < 0)
        return (-n);
    return (n);
}





int	ft_abs(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}

int ft_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int ft_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

int round_n(float n)
{
    if (n - (int)n < 0.5)
        return ((int)n);
    return ((int)n + 1);
}

static int ft_char_to_value(char c, const char *base_str)
{
    int i = 0;
    while (base_str[i] != '\0')
    {
        if (base_str[i] == c)
            return i;
        i++;
    }
    return -1;  // Invalid character for the given base
}

int ft_atoi_base(const char *str, const char *base_str)
{
    int i;
    int sign;
    int res;
    int base;
    int value;

    i = 0;
    sign = 1;
    res = 0;
    base = 0;

    // Determine the base by finding the length of base_str
    while (base_str[base] != '\0')
        base++;

    // Skip whitespace characters
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    
    // Check for sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    // Convert the string to an integer
    while ((value = ft_char_to_value(str[i], base_str)) != -1)
    {
        res = res * base + value;
        i++;
    }

    return (res * sign);
}

float degree_to_radian(int angle)
{
	return (angle * PI / 180);
}
