/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/31 21:12:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_angle(w_data *data)
{
	data->angle_x = ANGLE_VALUE;
	data->angle_y = ANGLE_VALUE;
	data->angle_z = ANGLE_VALUE;
}

void rotate_x(w_data *data)
{
	int i;
	int j;

	float cos_angle;
	float sin_angle;

	int angle_index; 

	int center_x;
	int center_y;

	int origin_x;
	int origin_y;

	int x;
	int y;
	
	int new_x;
	int new_y;

	// angle index
	angle_index = data->angle_x % DEGREE_MAX;
	if (angle_index < 0)
		angle_index += DEGREE_MAX;
	
	// center of the window
	center_x = data->window_width / 2;
	center_y = data->window_height / 2;
		
	// trigonometric values	
	cos_angle = data->lookup->cos_table[angle_index];
	sin_angle = data->lookup->sin_table[angle_index];


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
			
			// rotate
			new_x = (int)((x * cos_angle - y * sin_angle) / SCALE_TRIG);
			new_y = (int)((x * sin_angle + y * cos_angle) / SCALE_TRIG);

			// translate back
			data->points[i][j].x = (int)new_x + center_x;
			data->points[i][j].y = (int)new_y + center_y;
			
			j++;
		}			
		i++;
	}
}

void rotate_x_key(int key, w_data *data)
{
	if (key == Q)
		data->angle_x += ANGLE_VALUE;
	if (key == E)
		data->angle_x += ANGLE_VALUE * -1;

	data->angle_x %= DEGREE_MAX;
	if (data->angle_x < 0)
		data->angle_x += DEGREE_MAX;
	
}

void apply_rotation(w_data *data)
{
	rotate_x(data);
	update_img(data);
	draw_gui(data);	
}
