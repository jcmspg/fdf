/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:20:29 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_w_data *data, t_point *p0, t_point *p1)
{
	t_bres	bresen;
	float	color_step;
	float	color;

	bresen_calc(p0, p1, &bresen);
	color_step = (float)(p1->color - p0->color) / ft_max(bresen.dx, bresen.dy);
	color = (float)p0->color;
	while (1)
	{
		my_mlx_pixel_put(data, bresen.x0, bresen.y0, (int)color);
		if (bresen.x0 == p1->x && bresen.y0 == p1->y)
			break ;
		bresen.e2 = 2 * bresen.err;
		if (bresen.e2 > -bresen.dy)
		{
			bresen.err -= bresen.dy;
			bresen.x0 += increment(bresen.x0, p1->x);
		}
		if (bresen.e2 < bresen.dx)
		{
			bresen.err += bresen.dx;
			bresen.y0 += increment(bresen.y0, p1->y);
		}
		color += color_step;
	}
}

void	draw_horizontal(t_w_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols - 1)
		{
			draw_line(data, &data->p[i][j], &data->p[i][j + 1]);
			j++;
		}
		i++;
	}
}

void	draw_vertical(t_w_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->cols)
	{
		j = 0;
		while (j < data->grid->rows - 1)
		{
			draw_line(data, &data->p[j][i], &data->p[j + 1][i]);
			j++;
		}
		i++;
	}
}

void	draw_poly(t_w_data *data)
{
	if (data->mode != 'g')
	{
		draw_horizontal(data);
		draw_vertical(data);
	}
	if (data->mode == 'g')
		draw_poly_spherical(data);
}
