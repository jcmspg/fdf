/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:54:07 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/23 18:59:33 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int ft_atoi_base(const char *str, int base)
{
    int i;
    int sign;
    int res;

    i = 0;
    sign = 1;
    res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * base + str[i] - '0';
        i++;
    }
    return (res * sign);
}


