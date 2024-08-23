/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:15:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/23 17:56:19 by joamiran         ###   ########.fr       */
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
            points[i][j].x = j * (pointcalc(data));
            points[i][j].y = i * (pointcalc(data));
            points[i][j].z = 0;
            j++;

        }
        i++;
    }


    data->grid->half_x = (data->window_width / 2) - (points[0][cols - 1].x / 2);
    data->grid->half_y = (data->window_height / 2) - (points[lines - 1][0].y / 2);

    return (points);    
}
