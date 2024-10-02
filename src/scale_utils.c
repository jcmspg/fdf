/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:16:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:13:39 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_z(int key, t_w_data *data)
{
	if (key == S)
		data->scale_z += SCALE_FACTOR_Z;
	if (key == W)
		data->scale_z -= SCALE_FACTOR_Z;
}

static void	get_center(t_w_data *data, t_center *center)
{
	center->x = (float)data->window_w / 2.0f;
	center->y = (float)data->window_h / 2.0f;
}

void	calculate_new_zoom_position(t_w_data *data,
	int i, int j, t_center *center)
{
	float	scale;
	float	trans_x;
	float	trans_y;

	scale = data->scale_zoom;
	trans_x = data->p_b[i][j].x - center->x;
	trans_y = data->p_b[i][j].y - center->y;
	data->p[i][j].x = (int)(trans_x * scale + center->x);
	data->p[i][j].y = (int)(trans_y * scale + center->y);
	data->p[i][j].z = (int)(data->p_b[i][j].z * scale);
}

void	apply_zoom(t_w_data *data)
{
	t_center	center;
	int			i;
	int			j;

	get_center(data, &center);
	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			calculate_new_zoom_position(data, i, j, &center);
			j++;
		}
		i++;
	}
}
/* void apply_zoom(t_w_data *data)
{
	float center_x;
	float center_y;
	float scale;
	float trans_x;
	float trans_y;
	int i;
	int j;

	scale = data->scale_zoom;
	center_x = (float)data->window_w / 2.0f;
	center_y = (float)data->window_h / 2.0f;
	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			trans_x = data->p_b[i][j].x - center_x;
			trans_y = data->p_b[i][j].y - center_y;
			data->p[i][j].x = (int)(trans_x * scale + center_x);
			data->p[i][j].y = (int)(trans_y * scale + center_y);
			data->p[i][j].z = (int)(data->p_b[i][j].z * scale);
			j++;
		}
		i++;
	}
} */
