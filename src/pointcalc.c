/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointcalc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:31:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/21 21:08:17 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to calculate the coords of points based on the window size
// and the number of points in the map
//
// the function will calculate the center of the window and
// the distance between each point


int pointcalc (w_data *data, t_grid *grid)
{
    int height;
    int width;
    int square_size;

    t_point *center;

    center = center_point(data);

    printf("Window width: %d\n", data->window_width);
    printf("Window height: %d\n", data->window_height);

 
    height = ((data->window_height - (data->window_height / 10)) / grid->rows);
    width = ((data->window_width - (data->window_width / 10)) / grid->cols);


    if(height < width)
        square_size = height;
    else
        square_size = width;

    printf("Square size: %d\n", square_size);

    return (square_size);


}




t_point *center_point(w_data *data)
{
    t_point *center;

    center = (t_point *)malloc(sizeof(t_point));
    if (!center)
        return (NULL);

    center->x = data->window_width / 2;
    center->y = data->window_height / 2;

    printf("Center point: %d, %d\n", center->x, center->y);

    return (center);
}
