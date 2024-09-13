/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:20:29 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/13 19:47:00 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// BRESENHAM ALGORITHM
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
static int increment(int start, int end)
{
    if (start < end)
        return (1);
    return (-1);
}


static void bresen_calc (t_point *p0, t_point *p1, t_bres *bresen)
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

int height_to_color(int height, int min_height, int max_height)
{
    float percentage;
    int color;

    percentage = (float)(height - min_height) / (max_height - min_height);
    color = (int)(percentage * 255);
    return (color);
}

void my_mlx_pixel_put(w_data *data, int x, int y, int color)
{
    char    *distance;
    if (x < 0 || x >= data->window_width || y < 0 || y >= data->window_height)
        return;
    distance = data->img.address + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
    *(unsigned int *)distance = color;
}

void draw_line(w_data *data, t_point *p0, t_point *p1)
{
    t_bres bresen;
    bresen_calc(p0, p1, &bresen);

    int steps;
    float color_step;
    float color;

    steps = ft_max(bresen.dx, bresen.dy);
    color_step = (float)(p1->color - p0->color) / steps;
    color = (float)p0->color;

    while (1)
    {
     	my_mlx_pixel_put(data, bresen.x0, bresen.y0, (int)color);
        if (bresen.x0 == p1->x && bresen.y0 == p1->y)
            break;
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

void draw_poly_spherical(w_data *data)
{
	int i;
	int j;

	//draw lines in between the points, except when Z is negative
	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols - 1)
		{
			if (data->points[i][j].z >= 0 && data->points[i][j + 1].z >= 0)
			{
/* 				data->points[i][j].color = 0x000000;
				data->points[i][j + 1].color = 0x000000; */
				draw_line(data, &data->points[i][j], &data->points[i][j + 1]);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < data->grid->cols)
	{
		j = 0;
		while (j < data->grid->rows - 1)
		{
			if (data->points[j][i].z >= 0 &&  data->points[j + 1][i].z >= 0)
			{
/* 				data->points[i][j].color = 0x000000;
				data->points[j + 1][i].color = 0x000000; */
				draw_line(data, &data->points[j][i], &data->points[j + 1][i]);
			}
			j++;
		}
		i++;
	}
}


void draw_poly(w_data *data)
{
	int i;
	int j;

	i = 0;

//check if the mode is not spherical
	if (data->mode != 'g')
	{
	// draw horizontal lines between points in the same row for each column
		while (i < data->grid->rows)
		{
			j = 0;
			while (j < data->grid->cols - 1)
			{
				draw_line(data, &data->points[i][j], &data->points[i][j + 1]);
				j++;
			}
			i++;
		}
		// draw vertical lines between points in the same column for each row
		i = 0;
		while (i < data->grid->cols)
		{
			j = 0;
			while (j < data->grid->rows - 1)
			{
				draw_line(data, &data->points[j][i], &data->points[j + 1][i]);
				j++;
			}
			i++;
		}
	}
	if (data->mode == 'g')
		draw_poly_spherical(data);
}


