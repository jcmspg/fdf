/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:16:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/29 20:18:39 by joamiran         ###   ########.fr       */
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
void scale_grid(w_data *data)
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
			data->points[i][j].x *= scale_factor;
			data->points[i][j].y *= scale_factor;
			data->points[i][j].z *= scale_factor;
			j++;
		}
		i++;
	}
	data->scale = scale_factor;
}

void zoom(int keycode, w_data *data)
{
	int center_x;
	int center_y;

	int new_x;
	int new_y;

	int origin_x;
	int origin_y;

	int i;
	int j;

	
	if (keycode == UP)
		data->scale *= SCALE_FACTOR_IN;
	if (keycode == DOWN)
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
		
			new_x = (int)((origin_x - center_x) * data->scale + center_x);
			new_y = (int)((origin_y - center_y) * data->scale + center_y);
			
			data->points[i][j].x = new_x;
			data->points[i][j].y = new_y;
			j++;
		}
		i++;
	}
}

