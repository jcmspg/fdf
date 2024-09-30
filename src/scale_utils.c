/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:16:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/30 16:35:17 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
//	float trans_z;

	int i;
	int j;

	if (key == W)
		data->scale_zoom *= SCALE_FACTOR_IN;
	if (key == S)
		data->scale_zoom *= SCALE_FACTOR_OUT;

	if (data->scale_zoom < 0.1f)
		data->scale_zoom = 0.1f;
    if (data->scale_zoom > 10.0f)
		data->scale_zoom = 10.0f;

	center_x = (float)data->window_width / 2.0f;
	center_y = (float)data->window_height / 2.0f;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			origin_y = data->points_backup[i][j].y;
			origin_x = data->points_backup[i][j].x;

			trans_x = origin_x - center_x;
			trans_y = origin_y - center_y;
		//	trans_z = data->points_backup[i][j].z;


			new_x = trans_x * data->scale_zoom;
			new_y =trans_y * data->scale_zoom;

			data->points[i][j].x = new_x + center_x;
			data->points[i][j].y = new_y + center_y;


			/* data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].y = (int)data->points_backup[i][j].y;
 */

			j++;
		}
		i++;
	}
}












// function to scale the height of z values
void scale_z(int key, w_data *data)
{

	if (key == S)
		data->scale_z += SCALE_FACTOR_Z;
	if (key == W)
		data->scale_z -= SCALE_FACTOR_Z;
}


// funciton to normalize a Z value of a f_point
float normalize_z(float z, w_data *data)
{
	float z2;

	float normalization_factor;

	normalization_factor = 20 / logf(data->max_z + 1.0);

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
