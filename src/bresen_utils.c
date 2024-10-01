/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresen_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:24:33 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 16:25:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// BRESENHAM ALGORITHM
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
int	increment(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

void	bresen_calc(t_point *p0, t_point *p1, t_bres *bresen)
{
	bresen->x0 = p0->x;
	bresen->y0 = p0->y;
	bresen->z0 = p0->z;
	bresen->dx = ft_abs(p1->x - p0->x);
	bresen->dy = ft_abs(p1->y - p0->y);
	bresen->dz = ft_abs(p1->z - p0->z);
	bresen->err = bresen->dx - bresen->dy;
	bresen->e2 = 2 * bresen->err;
}
