/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:28:26 by joao              #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to reset the position of the p
void    reset_position(t_w_data *data)
{
    int i;
	int j;

    i = 0;
    if (data->p != NULL)
    {
        //assign p_b values to p
        while (i < data->grid->rows)
        {
			j = 0;
			while( j < data->grid->cols)
			{
				data->p[i][j].x = data->p_b[i][j].x;
				data->p[i][j].y = data->p_b[i][j].y;
				data->p[i][j].z = data->p_b[i][j].z;
				data->p[i][j].color = data->p_b[i][j].color;
				j++;
			}
			i++;
		}
	}
	data->scale_z = SCALE_FACTOR_Z;
}

void restore_origin(t_w_data *data)
{
	int i;
	int j;

	i = 0;
	if (data->p != NULL)
	{
		//assign p_b values to p
		while (i < data->grid->rows)
		{
			j = 0;
			while( j < data->grid->cols)
			{
				data->p_b[i][j].x = data->p_restore[i][j].x;
				data->p_b[i][j].y = data->p_restore[i][j].y;
				data->p_b[i][j].z = data->p_restore[i][j].z;
				data->p_b[i][j].color = data->p_restore[i][j].color;
				data->p[i][j].x = (int)data->p_b[i][j].x;
				data->p[i][j].y = (int)data->p_b[i][j].y;
				data->p[i][j].z = (int)data->p_b[i][j].z;
				data->p[i][j].color = data->p_b[i][j].color;
				j++;
			}
			i++;
		}
	}
	data->scale = 1;
}

//function get the movement values from the keyboard
void move(int keycode, t_w_data *data)
{
    int movement_x;
    int movement_y;

    int i;
    int j;

    movement_x = 0;
    movement_y = 0;

    if (keycode == W)
        movement_y = (data->window_h / MOVE_FACTOR);
    if (keycode == A)
        movement_x = (data->window_w / MOVE_FACTOR);
    if (keycode == S)
        movement_y = -(data->window_h / MOVE_FACTOR);
    if (keycode == D)
        movement_x = -(data->window_w / MOVE_FACTOR);

    i = 0;
    while(i < data->grid->rows)
    {
        j = 0;
        while(j < data->grid->cols)
        {
            data->p[i][j].x += movement_x;
            data->p[i][j].y += movement_y;

			data->p_b[i][j].x += movement_x;
			data->p_b[i][j].y += movement_y;

            j++;
        }
        i++;
    }
}

