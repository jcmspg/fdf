/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/13 18:59:45 by joamiran         ###   ########.fr       */
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

	float z;
	float y;

	float new_z;
	float new_y;

	float angle_z;

//	int center_x;
	int center_y;
	
	angle_z = degree_to_radian(data->angle);
	cos_angle = cos(angle_z);
	sin_angle = sin(angle_z);

//	center_x = data->window_width / 2;
	center_y = data->window_height / 2;
	
	i = 0;
	while(i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			z = data->points_backup[i][j].z;
			y = data->points_backup[i][j].y - center_y;

			// Apply rotation around the X-axis
			new_y = y * cos_angle - z * sin_angle;
			new_z =(y * sin_angle + z * cos_angle);

			// Store the result
			data->points_backup[i][j].y = new_y + center_y;
			data->points_backup[i][j].z = new_z;

			data->points[i][j].y = (int)data->points_backup[i][j].y;
			data->points[i][j].z = (int)data->points_backup[i][j].z;

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

	float z;
	float x;

	float new_z;
	float new_x;

	float angle_z;

	int center_x;
//	int center_y;
	
	angle_z = degree_to_radian(data->angle);
	cos_angle = cos(angle_z);
	sin_angle = sin(angle_z);

	center_x = data->window_width / 2;
//	center_y = data->window_height / 2;
	
	i = 0;
	while(i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			z = data->points_backup[i][j].z;
			x = data->points_backup[i][j].x - center_x;

			// Apply rotation around the X-axis
			new_x = x * cos_angle + z * sin_angle;
			new_z = (-x * sin_angle + z * cos_angle);

			// Store the result
			data->points_backup[i][j].x = new_x + center_x;
			data->points_backup[i][j].z = new_z;

			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].z = (int)data->points_backup[i][j].z;

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

	float x;
	float y;

	float new_x;
	float new_y;

	float angle_z;

	int center_x;
	int center_y;
	
	angle_z = degree_to_radian(data->angle);
	cos_angle = cos(angle_z);
	sin_angle = sin(angle_z);

	center_x = data->window_width / 2;
	center_y = data->window_height / 2;
	
	i = 0;
	while(i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			x = data->points_backup[i][j].x - center_x;
			y = data->points_backup[i][j].y - center_y;

			// Apply rotation around the Z-axis
			new_x = x * cos_angle - y * sin_angle;
			new_y = x * sin_angle + y * cos_angle;

			// Store the result
			data->points_backup[i][j].x = new_x + center_x;
			data->points_backup[i][j].y = new_y + center_y;

			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].y = (int)data->points_backup[i][j].y;

			j++;
		}
		i++;
	}
}

void rotate_z_key(int key, w_data *data)
{
	if (key == W)
	{
		if(data->angle_z >= 360)
			data->angle_z = 0;
		if(data->angle_z < 0)
			data->angle_z = 360;
		data->angle = ANGLE_VALUE;
		data->angle_z += ANGLE_VALUE;
	}
	if (key == S)
		{	
			if(data->angle_z >= 360)
				data->angle_z = 0;
			if(data->angle_z < 0)
				data->angle_z = 360;
			data->angle = -ANGLE_VALUE;
			data->angle_z -= ANGLE_VALUE;
		}

	transform_points(data);
//	z_assign(data);
}

void rotate_y_key(int key, w_data *data)
{
	if (key == A)
	{
		if(data->angle_y >= 360)
			data->angle_y = 0;
		if(data->angle_y < 0)
			data->angle_y = 360;
		data->angle = -ANGLE_VALUE;
		data->angle_y -= ANGLE_VALUE;
	}
	if (key == D)
		{
			if(data->angle_y >= 360)
				data->angle_y = 0;
			if(data->angle_y < 0)
				data->angle_y = 360;
			data->angle = ANGLE_VALUE;
			data->angle_y += ANGLE_VALUE;
		}
	transform_points(data);
//	z_assign(data);
}

void rotate_x_key(int key, w_data *data)
{
	if (key == Q)
	{
		if(data->angle_x >= 360)
			data->angle_x = 0;
		if(data->angle_x < 0)
			data->angle_x = 360;
		data->angle = -ANGLE_VALUE;
		data->angle_x -= ANGLE_VALUE;
	}
	if (key == E)
	{
		if(data->angle_x >= 360)
			data->angle_x = 0;
		if(data->angle_x < 0)
			data->angle_x = 360;
		data->angle = ANGLE_VALUE;
		data->angle_x += ANGLE_VALUE;
	}
	
	transform_points(data);
//	z_assign(data);
}
