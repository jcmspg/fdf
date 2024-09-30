/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:31:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/30 18:26:40 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to calculate the coords of p based on the window size
// and the number of p in the map
//
// the function will calculate the center of the window and
// the distance between each point

// the function will return the size of the square
// that will be used to draw the p
// the size will be the minimum between the height and the width of the window
int pointcalc (w_data *data)
{
    int height;
    int width;
    int distance;

   // t_point *center;

    //center = center_point(data);

    height = ((data->window_h - (data->window_h / 10)) / data->grid->rows);
    width = ((data->window_w - (data->window_w / 10)) / data->grid->cols);


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

    center->x = data->window_w / 2;
    center->y = data->window_h / 2;
    return (center);
}

// function to transform the 2d grid into a simulation of 3d (isometric)
// the function will change the coords of the p in the grid to simulate
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
            x_iso = data->p[i][j].x - data->p[i][j].y;
            y_iso = round_n((data->p[i][j].x + data->p[i][j].y) / 2.0);

            data->p[i][j].x = x_iso;
            data->p[i][j].y = y_iso;
			data->p[i][j].z = data->p[i][j].z;

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
			// normalize Z values
			data->p[i][j].z = (int)normalize_z(data->p_b[i][j].z, data);
			x = data->p[i][j].x;
			y = data->p[i][j].y;
			data->p[i][j].x =(int) (x - y) * cos(angle);
			data->p[i][j].y =(int) (x + y) * sin(angle) - data->p[i][j].z;

			j++;
		}
		i++;
	}
}

// assigning the z value to the p

//function to normalize the z values by changing the scale of the z axis



// function to add the Z value to the Y to simulate the 3d view
/* void z_assign(w_data *data)
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
			//data->p_b[i][j].z = normalize_z(data->p_b[i][j].z, data);
	    	z = data->p_b[i][j].z;

			data->p_b[i][j].z = z * data->scale_z;
		//	data->p_b[i][j].y -= z;
			data->p[i][j].y -= (int)data->p_b[i][j].z;
            j++;
        }
        j = 0;
        i++;
    }
} */

// colorize the p. if the color is not assigned, it will be assigned the default color
// if theres no color data in the whole map, we set colors for the various heights
// if there is color data, we assign the color to the p
// if the color data is invalid, we assign the default color
// if the color data is valid, we assign the color to the p
// the highest point will be red, the lowest will be blue
// the middle will be white; the p in between will be a gradient between the two colors
// the p in between will be a gradient between the two colors
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
            if (!data->p[i][j].color)
                data->p[i][j].color = STD_COLOR;
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
            z = data->p[i][j].z;
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
            data->p[i][j].color = color;
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
            z = data->p[i][j].z;
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
            data->p[i][j].color = color;
            j++;
        }
        j = 0;
        i++;
    }
}




f_point	**backup_p(w_data *data)
{
	int lines;
    int cols;
    int i;
    int j;
    f_point **p;

    lines = data->grid->rows;
    cols = data->grid->cols;

    p = (f_point **)ft_calloc(sizeof(f_point *) , (lines +1));
    if (!p)
    {
        fprintf(stderr, "Error: Could not allocate memory for p\n");
        exit(1);
    }
    i = 0;
    while (i < lines)
    {
        p[i] = (f_point *)ft_calloc(sizeof(f_point) , cols);
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
            p[i][j].x = data->p[i][j].x;
            p[i][j].y = data->p[i][j].y;
            p[i][j].z = data->p[i][j].z;
			p[i][j].color = data->p[i][j].color;
            j++;

        }
        i++;
    }
	return (p);
}

void change_backup (w_data *data)
{
	int lines;
    int cols;
    int i;
    int j;

	lines = data->grid->rows;
    cols = data->grid->cols;

	i = 0;

	 while (i < lines)
    {
        j = 0;
        while (j < cols)
        {
            data->p_b[i][j].x = data->p[i][j].x;
            data->p_b[i][j].z = data->p[i][j].z;
			data->p_b[i][j].color = data->p[i][j].color;
            data->p_b[i][j].y = data->p[i][j].y;
            j++;

        }
        i++;
    }
}
