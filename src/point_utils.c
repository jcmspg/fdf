/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:31:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/22 19:36:18 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to calculate the coords of points based on the window size
// and the number of points in the map
//
// the function will calculate the center of the window and
// the distance between each point

// the function will return the size of the square
// that will be used to draw the points
// the size will be the minimum between the height and the width of the window
int pointcalc (w_data *data)
{
    int height;
    int width;
    int distance;

   // t_point *center;

    //center = center_point(data);
 
    height = ((data->window_height - (data->window_height / 10)) / data->grid->rows);
    width = ((data->window_width - (data->window_width / 10)) / data->grid->cols);


    if(height < width)
        distance = (height);
    else
        distance = (width);

    return (distance);
}


// function to calculate the center of the window
t_point *center_point(w_data *data)
{
    t_point *center;

    center = (t_point *)malloc(sizeof(t_point));
    if (!center)
        return (NULL);

    center->x = data->window_width / 2;
    center->y = data->window_height / 2;
    return (center);
}

// function to transform the 2d grid into a simulation of 3d (isometric)
// the function will change the coords of the points in the grid to simulate
// a 3d view		yy = (t.img_h/2 + scale * ((numbers[n][0]) * sin(120) + (numbers[n][1]) * sin(120 + 2) + (numbers[n][2]) * sin(120 - 2)));


// function to calculate the isometric transformation
// x' = x-y
// y' = (x + y) / 2
// this rotates the grid 45 degrees and scales the y axis by 0.5
// in order to make the grid look like a 3d grid
void pcoords_iso(w_data *data)
{
    int i;
    int j;
    float x_iso;
    float y_iso;

    i = 0;
    j = 0;

    while (i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
            x_iso = data->points[i][j].x - data->points[i][j].y;
            y_iso = round_n((data->points[i][j].x + data->points[i][j].y) / 2.0);

            data->points[i][j].x = (int)x_iso;
            data->points[i][j].y = (int)y_iso;

            j++;
        }
        j = 0;
        i++;
    }
}

// assigning the z value to the points
void z_coords(w_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while( i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
            data->points[i][j].z = data->map[i][j];
            j++;
        }
        j = 0;
        i++;
    }
}

// function to add the Z value to the Y to simulate the 3d view
void z_assign(w_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
            data->points[i][j].y = (data->points[i][j].y + (data->points[i][j].z * 1));
            j++;
        }
        j = 0;
        i++;
    }
}

// colorize the points. The color will be set to red for now
void colorize(w_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
            data->points[i][j].color = 0xFF0000;
            j++;
        }
        j = 0;
        i++;
    }
}
