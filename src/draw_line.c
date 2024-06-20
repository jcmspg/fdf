/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:20:29 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/20 20:12:29 by joamiran         ###   ########.fr       */
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

/*
static void bresen_calc (point *p0, point *p1, t_bres *bresen)
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
*/

static void my_mlx_pixel_put(img_data *data, int x, int y, int color)
{
    char    *distance;

    distance = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)distance = color;
}
/*
void draw_line(w_data *window, point *p0, point *p1, int color)
{
    t_bres bresen;
    bresen_calc(p0, p1, &bresen);

    while (1)
    {
        my_mlx_pixel_put(&window->img, bresen.x0, bresen.y0, color);
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

void draw_poly(w_data *window, point *points, int color)
{
    point *tmp;

    tmp = points;
    while (tmp->next)
    {
        draw_line(window, tmp, tmp->next, color);
        tmp = tmp->next;
    }
    if (!tmp)
        tmp = points;
    draw_line(window, tmp, points, color);
}
*/

static void bresen_calc (int *p0, int *p1, t_bres *bresen)
{
    bresen->x0 = p0[0];
    bresen->y0 = p0[1];
    bresen->z0 = p0[2];
    bresen->dx = abs(p1[0] - p0[0]);
    bresen->dy = abs(p1[1] - p0[1]);
    bresen->dz = abs(p1[2] - p0[2]);
    bresen->err = bresen->dx - bresen->dy;
    bresen->e2 = 2 * bresen->err;
}


void draw_line(w_data *window, int *p0, int *p1, int color)
{
    t_bres bresen;
    bresen_calc(p0, p1, &bresen);

    while (1)
    {
        my_mlx_pixel_put(&window->img, bresen.x0, bresen.y0, color);
        if (bresen.x0 == p1[0] && bresen.y0 == p1[1])
            break;
        bresen.e2 = 2 * bresen.err;
        if (bresen.e2 > -bresen.dy)
        {
            bresen.err -= bresen.dy;
            bresen.x0 += increment(bresen.x0, p1[0]);
        }
        if (bresen.e2 < bresen.dx)
        {
            bresen.err += bresen.dx;
            bresen.y0 += increment(bresen.y0, p1[1]);
        }
    }
}

