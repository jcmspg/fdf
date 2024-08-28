/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:28:26 by joao              #+#    #+#             */
/*   Updated: 2024/08/29 00:17:41 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to reset the position of the points
void    reset_position(w_data *data)
{
    int i;

    i = 0;
    if (data->points != NULL)
    {
        //clear the points
        while (data->points[i])
        {
            free(data->points[i]);
            i++;
        }
        free(data->points);
    }
    
    //recreate the model
    recreate_model(data);
}



//function get the movement values from the keyboard
void	move(int keycode, w_data *data)
{
    int movement_x;
    int movement_y;
    
    int i;
    int j;
    
    movement_x = 0;
    movement_y = 0;

    if (keycode == W)
        movement_y = -(data->window_height / MOVE_FACTOR);
    if (keycode == A)
        movement_x = -(data->window_width / MOVE_FACTOR);
    if (keycode == S)
        movement_y = (data->window_height / MOVE_FACTOR);
    if (keycode == D)
        movement_x = (data->window_width / MOVE_FACTOR);
    
    i = 0;
    while(i < data->grid->rows)
    {
        j = 0;
        while(j < data->grid->cols)
        {
            data->points[i][j].x = data->points[i][j].x + movement_x;
            data->points[i][j].y = data->points[i][j].y + movement_y;
            j++;
        }
        i++;
    }
}



