/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/04 19:46:34 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_angle(w_data *data)
{
	data->angle = ANGLE_VALUE; 

	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;

	data->radius = 100;
}

void rotate_x(w_data *data)
{
	int i;
	int j;

	float cos_angle;
	float sin_angle;

	int angle_index; 

	float center_x;
	float center_y;

	float origin_x;
	float origin_y;

	float x;
	float y;
//	float z;
	
	//float new_x;
	float new_y;
	//float new_z;

	// angle index
	angle_index = data->angle % DEGREE_MAX;
	if (angle_index < 0)
		angle_index += DEGREE_MAX;
	
	// center of the window
	center_x = data->window_width / 2;
	center_y = data->window_height / 2;
		
	// trigonometric values	
	cos_angle = data->lookup->cos_table[angle_index] / SCALE_TRIG;
	sin_angle = data->lookup->sin_table[angle_index] / SCALE_TRIG;


	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			origin_x = data->points_backup[i][j].x;
			origin_y = data->points_backup[i][j].y;
	
			x = origin_x - center_x;
			y = origin_y - center_y;
		//	z = data->points_backup[i][j].z;
			
			// rotate

			new_y = ((y * cos_angle) - (/* z */ y * sin_angle));
			//new_z = ((y * sin_angle) + (z * cos_angle));

		
			// translate back
			data->points[i][j].x = (int)(x + center_x);
			data->points[i][j].y = (int)(new_y + center_y);

			data->points_backup[i][j].x = x + center_x;
			data->points_backup[i][j].y = new_y + center_y;
			//data->points_backup[i][j].z = new_z;

			j++;
		}			
		i++;
	}
}

void rotate_y(w_data *data)
{
	int i;
	int j;

	float cos_angle;
	float sin_angle;

	int angle_index;

	float center_x;
	float center_y;

	float origin_x;
	float origin_y;

	float x;
	float y;
//	float z;

	float new_x;
	//float new_y;
	// float new_z;

	// angle index
	angle_index = data->angle % DEGREE_MAX;
	if (angle_index < 0)
		angle_index += DEGREE_MAX;

	// center of the window
	center_x = data->window_width / 2;
	center_y = data->window_height / 2;

	// trigonometric values
	cos_angle = data->lookup->cos_table[angle_index] / SCALE_TRIG;
	sin_angle = data->lookup->sin_table[angle_index] / SCALE_TRIG;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			origin_x = data->points_backup[i][j].x;
			origin_y = data->points_backup[i][j].y;

			x = origin_x - center_x;
			y = origin_y - center_y;
		//	z = data->points_backup[i][j].z;

			// rotate

			new_x = ((x * cos_angle) + (y /*z */  * sin_angle));
			//new_z = ((-x * sin_angle) + (z * cos_angle));
			//new_y = ((y * sin_angle) - (x * cos_angle)) / SCALE_TRIG;

			// translate back
			data->points[i][j].x = (int)((new_x) + center_x);
			data->points[i][j].y = (int)(y + center_y);

			data->points_backup[i][j].x = (new_x) + center_x;
			data->points_backup[i][j].y = y + center_y;
			//data->points_backup[i][j].z = new_z;
			
			j++;
		}
		i++;
	}
}

void rotate_z(w_data *data)
{
	int i;
	int j;

	float cos_angle;
	float sin_angle;

	int angle_index;
	
	float center_x;
	float center_y;

	float origin_x;
	float origin_y;

	float x;
	float y;
	//float z;
	
	float new_x;
	float new_y;
	//float new_z;

	// angle index
	angle_index = data->angle % DEGREE_MAX;
	if (angle_index < 0)
		angle_index += DEGREE_MAX;

	// center of the window
	center_x = data->window_width / 2;
	center_y = data->window_height / 2;

	// trigonometric values
	cos_angle = data->lookup->cos_table[angle_index] / SCALE_TRIG;
	sin_angle = data->lookup->sin_table[angle_index] / SCALE_TRIG;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			origin_x = data->points_backup[i][j].x;
			origin_y = data->points_backup[i][j].y;

			x = origin_x - center_x;
			y = origin_y - center_y;
			//z = data->points_backup[i][j].z;

			// rotate

			new_x = ((x * cos_angle) - (y * sin_angle));
			new_y = ((y * cos_angle) + (x * sin_angle));
			// new_z = z;

			// translate back
			data->points[i][j].x = (int)(new_x + center_x);
			data->points[i][j].y = (int)(new_y + center_y);

			data->points_backup[i][j].x = new_x + center_x;
			data->points_backup[i][j].y = new_y + center_y;

			j++;
		}
		i++;
	}
}
void rotate_z_key(int key, w_data *data)
{
	if (key == W)
	{
		data->angle = ANGLE_VALUE;
		data->angle_z += ANGLE_VALUE;
	}
	if (key == S)
	{
		data->angle = -ANGLE_VALUE;
		data->angle_z -= ANGLE_VALUE;
	}

	data->angle_z %= DEGREE_MAX;
	if (data->angle_z < 0)
		data->angle_z += DEGREE_MAX;
}

void rotate_y_key(int key, w_data *data)
{
	if (key == A)
		{
			data->angle = -ANGLE_VALUE;
			data->angle_y -= ANGLE_VALUE;
		}
	if (key == D)
	{
		data->angle = ANGLE_VALUE;
		data->angle_y += ANGLE_VALUE;
	}

	data->angle_y %= DEGREE_MAX;
	if (data->angle_y < 0)
		data->angle_y += DEGREE_MAX;
}

void rotate_x_key(int key, w_data *data)
{
	if (key == Q)
	{
		data->angle = ANGLE_VALUE;
		data->angle_x += ANGLE_VALUE;
	}
	if (key == E)
	{
		data->angle = -ANGLE_VALUE;
		data->angle_x -= ANGLE_VALUE;
	}

	data->angle_x %= DEGREE_MAX;
	if (data->angle_x < 0)
		data->angle_x += DEGREE_MAX;
	
}

/* void z_assign_r(w_data *data)
{
    int i;
    int j;

    float sin_angle_x;
    float sin_angle_y;

    float cos_angle_x;
    float cos_angle_y;

    sin_angle_x = data->lookup->sin_table[data->angle_x] / SCALE_TRIG;
    sin_angle_y = data->lookup->sin_table[data->angle_y] / SCALE_TRIG;

    cos_angle_x = data->lookup->cos_table[data->angle_x] / SCALE_TRIG;
    cos_angle_y = data->lookup->cos_table[data->angle_y] / SCALE_TRIG;
    
    float x;
    float y;
    float z;
    
    float new_y;
    float new_x;
    float new_z;

    i = 0;
    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            x = data->points_backup[i][j].x;
            y = data->points_backup[i][j].y;
            z = data->points_backup[i][j].z;

			z *= data->scale_z;

            // Rotate around the x-axis
            new_y = y * cos_angle_x - z * sin_angle_x;
            new_z = y * sin_angle_x + z * cos_angle_x;

            // Rotate around the y-axis
            new_x = x * cos_angle_y + new_z * sin_angle_y;
            new_z = -x * sin_angle_y + new_z * cos_angle_y;

            data->points[i][j].x = new_x;
            data->points[i][j].z = new_z;
            data->points[i][j].y = new_y - new_z;

            j++;
        }
        i++;
    }
} */
