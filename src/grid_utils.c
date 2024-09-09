/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:15:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/09 20:22:47 by joamiran         ###   ########.fr       */
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
            data->points[i][j].x += data->grid->half_x;
            data->points[i][j].y += data->grid->half_y;
            j++;
        }
        i++;
    }
}


// make array of points to then assign coordinates to them
t_point **make_points(w_data *data)
{
    int lines;
    int cols;
    int i;
    int j;
    t_point **points;

    lines = data->grid->rows;
    cols = data->grid->cols;
    
    points = (t_point **)ft_calloc(sizeof(t_point *) , (cols * lines));
    if (!points)
    {
        fprintf(stderr, "Error: Could not allocate memory for points\n");
        exit(1);
    }
    i = 0;
    while (i < lines)
    {
        points[i] = (t_point *)ft_calloc(sizeof(t_point) , cols);
        if (!points[i])
        {
            fprintf(stderr, "Error: Could not allocate memory for points\n");
            while (i >= 0)
            {
                free(points[i]);
                i--;
            }
            free(points);
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < lines)
    {
        j = 0;
        while (j < cols)
        {
            points[i][j].x = (int)j * (pointcalc(data));
            points[i][j].y = (int)i * (pointcalc(data));
            points[i][j].z = 0;
            j++;

        }
        i++;
    }


    data->grid->half_x = (data->window_width / 2) - (points[0][cols - 1].x / 2);
    data->grid->half_y = (data->window_height / 2) - (points[lines - 1][0].y / 2);

    return (points);    
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

    min_x = data->points[0][0].x;
    min_y = data->points[0][0].y;
   
    max_x = data->points[0][0].x;
    max_y = data->points[0][0].y;

    i = 0;
    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            if (data->points[i][j].x < min_x)
                min_x = data->points[i][j].x;
            if (data->points[i][j].y < min_y)
                min_y = data->points[i][j].y;
            if (data->points[i][j].x > max_x)
                max_x = data->points[i][j].x;
            if (data->points[i][j].y > max_y)
                max_y = data->points[i][j].y;
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

    vp_width = data->window_width - (data->window_width / 10);
    vp_height = data->window_height - (data->window_height / 10);
    
    if (data->grid->width > data->grid->height)
        data->scale = (float)vp_width / data->grid->width;
    else
        data->scale = (float)vp_height / data->grid->height;

    data->mid_x = (data->grid->max_x + data->grid->min_x) / 2;
    data->mid_y = (data->grid->max_y + data->grid->min_y) / 2;

    data->grid->half_x = data->window_width / 2;
    data->grid->half_y = data->window_height / 2;
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
            data->points[i][j].x = (data->points[i][j].x - data->mid_x) * scale + data->grid->half_x;
            data->points[i][j].y = (data->points[i][j].y - data->mid_y) * scale + data->grid->half_y;
			data->points[i][j].z = data->points[i][j].z;		
            j++;
        }
        i++;
    }
}

void backup_data(w_data *data)
{
	data->points_backup = backup_points(data);
	data->points_restore = backup_points(data);
}

static void set_origin(w_data *data)
{
	calc_sc_mid(data);
	scale_center(data);
	data->points_backup = backup_points(data);
}

void build_model(w_data *data)
{
	backup_data(data);
	pcoords_iso(data);
	set_origin(data);
//	z_assign(data);
	color_mode(data);
//	backup_data(data);
	draw_poly(data);
}

