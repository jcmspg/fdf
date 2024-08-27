/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:31:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/27 21:12:03 by joamiran         ###   ########.fr       */
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
            data->points[i][j].y = (data->points[i][j].y - (data->points[i][j].z * SCALE_FACTOR_Z));
            j++;
        }
        j = 0;
        i++;
    }
}

// colorize the points. if the color is not assigned, it will be assigned the default color
// if theres no color data in the whole map, we set colors for the various heights
// if there is color data, we assign the color to the points
// if the color data is invalid, we assign the default color
// if the color data is valid, we assign the color to the points
// the highest point will be red, the lowest will be blue
// the middle will be white; the points in between will be a gradient between the two colors
// the points in between will be a gradient between the two colors
//
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
            if (!data->points[i][j].color)
                data->points[i][j].color = STD_COLOR;
            j++;
        }
        j = 0;
        i++;
    }
}

void colorize_gradient(w_data *data)
{
    int i;
    int j;
    int max;
    int min;
    int range;
    int color;
    int red;
    int green;
    int blue;

    double ratio;

    i = 0;
    j = 0;
    max = data->max_z;
    min = data->min_z;
    range = max - min;

    if (range == 0)
        range = 1;
    
    while (i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
            if (data->points[i][j].z == max)
                color = MAX_COLOR;
            else if (data->points[i][j].z == 0)
                color = WHITE;
            else if (data->points[i][j].z == min)
                color = MIN_COLOR;
            else
            {
                // the ratio will be the percentage of the height of the point
                ratio = ((double)data->points[i][j].z - min) / range;
                red = (int)((1 - ratio) * 255);
                green = 0;
                blue = (int)(ratio * 255);

                color = (red * 256 * 256) + (green * 256) + blue;
            }
            data->points[i][j].color = color;
            j++;
        }
        j = 0;
        i++;
    }
}

/*
void colorize_gradient(w_data *data)
{
    int i;
    int j;
    int max;
    int min;
    int range;
    int color;
    int red;
    int green;
    int blue;
    int z;

    double ratio;

    i = 0;
    j = 0;
    max = data->max_z;
    min = data->min_z;
    range = max - min;

    if (range == 0)
        range = 1;
    
    while (i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
            z = data->points[i][j].z;

            if (z == max)
                color = MAX_COLOR;
            else if (z == 0)
                color = WHITE;
            else if (z == min)
                color = MIN_COLOR;
            else
            {
                ratio = ((double)(z - min) / range);

                if (z > 0)
                {
                    ratio = (double)z / max;
                    red = (int)(255 * ratio);
                    green = (int)(255 * (1 - ratio);
                    blue = (int)(255 * (1 - ratio));
                }
                else
                {
                    ratio = (double)(z - min) / range;
                    red = (int)(255 * (1 - ratio));
                    green = (int)(255 * (1 - ratio));
                    blue = 255;
                }

                if (red < 0)
                    red = 0;
                else if (red > 255)
                    red = 255;
                if (green < 0)
                    green = 0;
                else if (green > 255)
                    green = 255;
                if (blue < 0)
                    blue = 0;
                else if (blue > 255)
                    blue = 255;
                }
                color = (red * 0x10000) | (green * 0x100) | blue;
            }
            data->points[i][j].color = color;
            j++;
            printf("Point[%d][%d]: z=%d, red=%d, green=%d, blue=%d, color=%06x\n", 
       i, j, data->points[i][j].z, red, green, blue, color);
        }
        j = 0;
        i++;
    }
}
*/
