/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:15:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/30 18:26:40 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//center_grid: centers the grid in the window
//
//
void center_grid (w_data *data)
{
    int i;
    int j;
    int lines;
    int cols;

    lines = data->grid->rows;
    cols = data->grid->cols;


    i = 0;
    while (i < lines)
    {
        j = 0;
        while (j < cols)
        {
            data->p[i][j].x += data->grid->half_x;
            data->p[i][j].y += data->grid->half_y;
            j++;
        }
        i++;
    }
}


// make array of p to then assign coordinates to them
t_point **make_p(w_data *data)
{
    int lines;
    int cols;
    int i;
    int j;
    t_point **p;

    lines = data->grid->rows;
    cols = data->grid->cols;

    p = (t_point **)ft_calloc(sizeof(t_point *) , (lines+1));
    if (!p)
    {
        fprintf(stderr, "Error: Could not allocate memory for p\n");
        exit(1);
    }
    i = 0;
    while (i < lines)
    {
        p[i] = (t_point *)ft_calloc(sizeof(t_point) , cols);
        if (!p[i])
        {
            fprintf(stderr, "Error: Could not allocate memory for p\n");
            while (i >= 0)
            {
                free(p[i]);
                i--;
            }
            free(p);
            exit(1);
        }
        i++;
    }
	p[lines] = NULL;
    i = 0;
    while (i < lines)
    {
        j = 0;
        while (j < cols)
        {
            p[i][j].x = (int)j * (pointcalc(data));
            p[i][j].y = (int)i * (pointcalc(data));
            p[i][j].z = 0;
            j++;

        }
        i++;
    }


    data->grid->half_x = (data->window_w / 2) - (p[0][cols - 1].x / 2);
    data->grid->half_y = (data->window_h / 2) - (p[lines - 1][0].y / 2);

    return (p);
}

// calc_boundaries: calculates the boundaries of the grid
void calc_boundaries(w_data *data)
{
    int min_x;
    int min_y;
    int max_x;
    int max_y;

    int i;
    int j;

    min_x = data->p[0][0].x;
    min_y = data->p[0][0].y;

    max_x = data->p[0][0].x;
    max_y = data->p[0][0].y;

    i = 0;
    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            if (data->p[i][j].x < min_x)
                min_x = data->p[i][j].x;
            if (data->p[i][j].y < min_y)
                min_y = data->p[i][j].y;
            if (data->p[i][j].x > max_x)
                max_x = data->p[i][j].x;
            if (data->p[i][j].y > max_y)
                max_y = data->p[i][j].y;
            j++;
        }
        i++;
    }
    data->grid->min_x = min_x;
    data->grid->min_y = min_y;
    data->grid->max_x = max_x;
    data->grid->max_y = max_y;
}

// calc_sc_mid: calculates the middle of the screen and the scale
void calc_sc_mid(w_data *data)
{
    calc_boundaries(data);

    int vp_width;
    int vp_height;

    data->grid->width = data->grid->max_x - data->grid->min_x;
    data->grid->height = data->grid->max_y - data->grid->min_y;

    vp_width = data->window_w - (data->window_w / 10);
    vp_height = data->window_h - (data->window_h / 10);

    if (data->grid->width > data->grid->height)
        data->scale = (float)vp_width / data->grid->width;
    else
        data->scale = (float)vp_height / data->grid->height;

    data->mid_x = (data->grid->max_x + data->grid->min_x) / 2;
    data->mid_y = (data->grid->max_y + data->grid->min_y) / 2;

    data->grid->half_x = data->window_w / 2;
    data->grid->half_y = data->window_h / 2;
}

void scale_center(w_data *data)
{
    int i;
    int j;
    float scale;

    scale = data->scale;
    i = 0;

    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            data->p[i][j].x = (data->p[i][j].x - data->mid_x) * scale + data->grid->half_x;
            data->p[i][j].y = (data->p[i][j].y - data->mid_y) * scale + data->grid->half_y;
			data->p[i][j].z = data->p[i][j].z;
            j++;
        }
        i++;
    }
}

void backup_data(w_data *data)
{
	data->p_b = backup_p(data);

	data->p_restore = backup_p(data);
}

static void set_origin(w_data *data)
{
	calc_sc_mid(data);
	scale_center(data);
	change_backup(data);
	//data->p_b = backup_p(data);
}

void build_model(w_data *data)
{
	//backup_data(data);
	pcoords_iso(data);
	set_origin(data);
//	z_assign(data);
	color_mode(data);
//	backup_data(data);
	draw_poly(data);
}

