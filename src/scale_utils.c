/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:16:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/05 21:21:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Functions to scale the map
//
// determining the maximum grid size
//

//
//
// scaling function to fit the window
/* void scale_grid(w_data *data)
{
	int i;
	int j;
	int scale_factor_x;
	int scale_factor_y;
	int scale_factor;

	scale_factor_x = data->window_width / data->grid->cols / 2;
	scale_factor_y = data->window_height / data->grid->rows / 2;


	if (scale_factor_x < scale_factor_y)
		scale_factor = scale_factor_x;
	else
		scale_factor = scale_factor_y;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			data->points_backup[i][j].x *= scale_factor;
			data->points_backup[i][j].y *= scale_factor;
			data->points_backup[i][j].z *= scale_factor;

			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].y = (int)data->points_backup[i][j].y;
			data->points[i][j].z = (int)data->points_backup[i][j].z;
			
			j++;
		}
		i++;
	}
	data->scale = scale_factor;
} */

void zoom(int key, w_data *data)
{
	float center_x;
	float center_y;

	float new_x;
	float new_y;

	float origin_x;
	float origin_y;

	float trans_x;
	float trans_y;

	int i;
	int j;

	data->scale = 1.0f;

	if (key == W)
		data->scale *= SCALE_FACTOR_IN;
	if (key == S)
		data->scale *= SCALE_FACTOR_OUT;

	if (data->scale < 0.1f)
		data->scale = 0.1f;
	if (data->scale > 10.0f)
		data->scale = 10.0f;

	center_x = data->window_height / 2;
	center_y = data->window_width / 2;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			origin_x = data->points_backup[i][j].x;
			origin_y = data->points_backup[i][j].y;

			trans_x = origin_x - center_x;
			trans_y = origin_y - center_y;

			new_y = (trans_y  * data->scale);
			new_x = (trans_x  * data->scale);
			
			data->points_backup[i][j].x = new_x + center_x;
			data->points_backup[i][j].y = new_y + center_y;
			
			
			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].y = (int)data->points_backup[i][j].y;
			
			j++;
		}
		i++;
	}
}

// function to scale the height of z values
void scale_z(int key, w_data *data)
{

	if (key == S)
		data->scale_z -= SCALE_FACTOR_Z;
	if (key == W)
		data->scale_z += SCALE_FACTOR_Z;
}

void z_assign_backup(w_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			// Adjust y based on z and scale_z
            data->points_backup[i][j].y -= (data->points_backup[i][j].z * data->scale_z);
            j++;
		}
		i++;
	}
	data->scale_z = 0;
}

// funciton to normalize a Z value of a f_point
float normalize_z(float z, w_data *data)
{
	float z2;

	float normalization_factor;

	normalization_factor = 100 / logf(data->max_z + 1.0);

	if (z >= 0)
		z2 = logf(z + 1.0f) * normalization_factor;

	else
		z2 = -logf(-z + 1.0f) * normalization_factor;

	
	return (z2);
}



void normalize_z_log(w_data *data)
{
	int i;
	int j;

	int max_z;
	float z;
	float z2;

	float normalization_factor;
	float epsilon;


	epsilon = 0.0001;
	max_z = data->max_z;

	normalization_factor = log(max_z + 1) / log(max_z + 1 + epsilon);

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			z = data->points_backup[i][j].z;

			if (z < 0)
				z2 = log(z + 1) * normalization_factor * -1;

			else
				z2 = log(z + 1) * normalization_factor * 1;

			data->points_backup[i][j].z = z2;

			j++;
		}
		i++;
	}
}
