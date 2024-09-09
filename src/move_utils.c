/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:28:26 by joao              #+#    #+#             */
/*   Updated: 2024/09/09 19:57:47 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to reset the position of the points
void    reset_position(w_data *data)
{
    int i;
	int j;

    i = 0;
    if (data->points != NULL)
    {
        //assign points_backup values to points
        while (i < data->grid->rows)
        {
			j = 0;
			while( j < data->grid->cols)
			{
				data->points[i][j].x = data->points_backup[i][j].x;
				data->points[i][j].y = data->points_backup[i][j].y;
				data->points[i][j].z = data->points_backup[i][j].z;
				data->points[i][j].color = data->points_backup[i][j].color;
				j++;
			}
			i++;
		}
	}
	data->scale_z = SCALE_FACTOR_Z;
}

void restore_origin(w_data *data)
{
	int i;
	int j;

	i = 0;
	if (data->points != NULL)
	{
		//assign points_backup values to points
		while (i < data->grid->rows)
		{
			j = 0;
			while( j < data->grid->cols)
			{
				data->points[i][j].x = data->points_restore[i][j].x;
				data->points[i][j].y = data->points_restore[i][j].y;
				data->points[i][j].z = data->points_restore[i][j].z;
				data->points[i][j].color = data->points_restore[i][j].color;
				data->points_backup[i][j].x = data->points_restore[i][j].x;
				data->points_backup[i][j].y = data->points_restore[i][j].y;
				data->points_backup[i][j].z = data->points_restore[i][j].z;
				data->points_backup[i][j].color = data->points_restore[i][j].color;
				j++;
			}
			i++;
		}
	}
	data->scale = 1;
}

//function get the movement values from the keyboard
void move(int keycode, w_data *data)
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
            data->points[i][j].x += movement_x;
            data->points[i][j].y += movement_y;

			data->points_backup[i][j].x += movement_x;
			data->points_backup[i][j].y += movement_y;
			
            j++;
        }
        i++;
    }
}
