/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:31:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/09 19:20:34 by joamiran         ###   ########.fr       */
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
/* void pcoords_iso(w_data *data)
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

            data->points[i][j].x = x_iso;
            data->points[i][j].y = y_iso;
			data->points[i][j].z = data->points[i][j].z;

            j++;
        }
        j = 0;
        i++;
    }
} */



void pcoords_iso(w_data *data)
{
	float angle;
	int i;
	int j;
	float x;
	float y;

	angle = degree_to_radian(30);
	i = 0;
	while(i < data->grid->rows)
	{
		j = 0;
		while(j < data->grid->cols)
		{
			x = data->points[i][j].x;
			y = data->points[i][j].y;
			data->points[i][j].x =(int) (x - y) * cos(angle);
			data->points[i][j].y =(int) (x + y) * sin(angle);
			j++;
		}
		i++;
	}
}

// assigning the z value to the points

//function to normalize the z values by changing the scale of the z axis


   
// function to add the Z value to the Y to simulate the 3d view
void z_assign(w_data *data)
{
    int i;
    int j;

	float z;

    i = 0;
    j = 0;

	data->scale_z = SCALE_FACTOR_Z;

    while (i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
			//data->points_backup[i][j].z = normalize_z(data->points_backup[i][j].z, data);
	    	z = data->points_backup[i][j].z;
			
			data->points_backup[i][j].z = z * data->scale_z;
		//	data->points_backup[i][j].y -= z;
			data->points[i][j].y -= (int)data->points_backup[i][j].z;
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
            if (z == 0)
                color = STD_COLOR;
            else if (z == max)
                color = MAX_COLOR;
            else if (z == min)
                color = MIN_COLOR;
            else
            {
                // the ratio will be the percentage of the height of the point
                ratio = ((double)z - min) / range;
                
                // if z > 0, interpolate between white and red
                if (z > 0)
                {
                    red = (int)(ratio * 255);
                    green = (int)((1 - ratio) * 255);
                    blue = 255 * (1 - ratio);
                }
                // if z < 0, interpolate between white and blue
                else
                {
                    red = (int)(255 * (1 + ratio));
                    green = (int)((1 - ratio) * 255);
                    blue = (int)(-ratio * 255);
                }
                
                color = (red << 16) + (green << 8) + blue;
            }
            data->points[i][j].color = color;
            j++;
        }
        j = 0;
        i++;
    }
}

// colorize but in grayscale
void colorize_grayscale(w_data *data)
{
    int i;
    int j;
    int max;
    int min;
    int range;
    int color;
    int z;
    int gray;

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
            if (z == 0)
                color = MEDIUM_GRAY;
            else if (z == max)
                color = LIGHT_GRAY;
            else if (z == min)
                color = DARK_GRAY;
            else
            {
                // the ratio will be the percentage of the height of the point
                ratio = ((double)z - min) / range;
                
                // interpolate between black and white
                gray = (int)(64 + ratio * (192 - 64));

                // assign the color
                color = (gray << 16) + (gray << 8) + gray;
            }
            data->points[i][j].color = color;
            j++;
        }
        j = 0;
        i++;
    }
}




f_point	**backup_points(w_data *data)
{
	int lines;
    int cols;
    int i;
    int j;
    f_point **points;

    lines = data->grid->rows;
    cols = data->grid->cols;
    
    points = (f_point **)ft_calloc(sizeof(f_point *) , (cols * lines));
    if (!points)
    {
        fprintf(stderr, "Error: Could not allocate memory for points\n");
        exit(1);
    }
    i = 0;
    while (i < lines)
    {
        points[i] = (f_point *)ft_calloc(sizeof(f_point) , cols);
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
            points[i][j].x = data->points[i][j].x;
            points[i][j].y = data->points[i][j].y;
            points[i][j].z = data->points[i][j].z;
			points[i][j].color = data->points[i][j].color;
            j++;

        }
        i++;
    }
	return (points);
}
