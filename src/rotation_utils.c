/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_angle(t_w_data *data)
{
	data->angle = ANGLE_VALUE;

	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;

	data->radius = 100;
}

void rotate_x(t_w_data *data)
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

//	center_x = data->window_w / 2;
	center_y = data->window_h / 2;

	i = 0;
	while(i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			z = data->p_b[i][j].z;
			y = data->p_b[i][j].y - center_y;

			// Apply rotation around the X-axis
			new_y = y * cos_angle - z * sin_angle;
			new_z =(y * sin_angle + z * cos_angle);

			// Store the result
			data->p_b[i][j].y = new_y + center_y;
			data->p_b[i][j].z = new_z;

	/* 		data->p[i][j].y = (int)data->p_b[i][j].y;
			data->p[i][j].z = (int)data->p_b[i][j].z;
 */
			j++;
		}
		i++;
	}
	apply_zoom(data);
}

void rotate_y(t_w_data *data)
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

	center_x = data->window_w / 2;
//	center_y = data->window_h / 2;

	i = 0;
	while(i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			z = data->p_b[i][j].z;
			x = data->p_b[i][j].x - center_x;

			// Apply rotation around the X-axis
			new_x = x * cos_angle + z * sin_angle;
			new_z = (-x * sin_angle + z * cos_angle);

			// Store the result
			data->p_b[i][j].x = new_x + center_x;
			data->p_b[i][j].z = new_z;

			/* data->p[i][j].x = (int)data->p_b[i][j].x;
			data->p[i][j].z = (int)data->p_b[i][j].z;
 */
			j++;
		}
		i++;
	}
	apply_zoom(data);
}

void rotate_z(t_w_data *data)
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

	center_x = data->window_w / 2;
	center_y = data->window_h / 2;

	i = 0;
	while(i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			x = data->p_b[i][j].x - center_x;
			y = data->p_b[i][j].y - center_y;

			// Apply rotation around the Z-axis
			new_x = x * cos_angle - y * sin_angle;
			new_y = x * sin_angle + y * cos_angle;

			// Store the result
			data->p_b[i][j].x = new_x + center_x;
			data->p_b[i][j].y = new_y + center_y;

			data->p[i][j].x = (int)data->p_b[i][j].x;
			data->p[i][j].y = (int)data->p_b[i][j].y;

			j++;
		}
		i++;
	}
}

void rotate_z_key(int key, t_w_data *data)
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

	transform_p(data);
//	z_assign(data);
}

void rotate_y_key(int key, t_w_data *data)
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
	transform_p(data);
//	z_assign(data);
}

void rotate_x_key(int key, t_w_data *data)
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

	transform_p(data);
//	z_assign(data);
}
