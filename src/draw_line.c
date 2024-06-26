/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:20:29 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/21 21:06:45 by joamiran         ###   ########.fr       */
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
    bresen->dx = abs(p1->x - p0->x);
    bresen->dy = abs(p1->y - p0->y);
    bresen->dz = abs(p1->z - p0->z);
    bresen->err = bresen->dx - bresen->dy;
    bresen->e2 = 2 * bresen->err;
}


static void my_mlx_pixel_put(w_data *data, int x, int y, int color)
{
    char    *distance;
    if (x < 0 || x >= data->window_width || y < 0 || y >= data->window_height)
        return;
    distance = data->img.address + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
    *(unsigned int *)distance = color;
}

void draw_line(w_data *window, t_point *p0, t_point *p1, int color)
{
    t_bres bresen;
    bresen_calc(p0, p1, &bresen);

    while (1)
    {
        my_mlx_pixel_put(window, bresen.x0, bresen.y0, color);
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
    }
}

void draw_poly(w_data *window, t_grid *grid, t_point **points, int color)
{
    int i;
    int j;

    i = 0;
    // draw horizontal lines between points in the same row for each column
    while (i < grid->rows)
    {
        j = 0;
        while (j < grid->cols - 1)
        {
            draw_line(window, &points[i][j], &points[i][j + 1], color);
            j++;
        }
        i++;
    }
    // draw vertical lines between points in the same column for each row
    i = 0;
    while (i < grid->cols)
    {
        j = 0;
        while (j < grid->rows - 1)
        {
            draw_line(window, &points[j][i], &points[j + 1][i], color);
            j++;
        }
        i++;
    }
}
