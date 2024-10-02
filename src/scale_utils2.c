/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:03:13 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:09:24 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_scale_zoom(int key, t_w_data *data)
{
	if (key == W)
		data->scale_zoom *= SCALE_FACTOR_IN;
	else if (key == S)
		data->scale_zoom *= SCALE_FACTOR_OUT;
	if (data->scale_zoom < 0.1f)
		data->scale_zoom = 0.1f;
	if (data->scale_zoom > 10.0f)
		data->scale_zoom = 10.0f;
}

void	calculate_new_position(t_w_data *data, int i, int j, t_center *center)
{
	data->p[i][j].x = (data->p_b[i][j].x - center->x)
		* data->scale_zoom + center->x;
	data->p[i][j].y = (data->p_b[i][j].y - center->y)
		* data->scale_zoom + center->y;
}

void	get_center(t_w_data *data, t_center *center)
{
	center->x = (float)data->window_w / 2.0f;
	center->y = (float)data->window_h / 2.0f;
}

void	zoom(int key, t_w_data *data)
{
	t_center	center;
	int			i;
	int			j;

	update_scale_zoom(key, data);
	get_center(data, &center);
	i = -1;
	while (++i < data->grid->rows)
	{
		j = -1;
		while (++j < data->grid->cols)
		{
			calculate_new_position(data, i, j, &center);
		}
	}
}
/* void	update_scale_zoom(int key, t_w_data *data)
{
	if (key == W)
		data->scale_zoom *= SCALE_FACTOR_IN;
	if (key == S)
		data->scale_zoom *= SCALE_FACTOR_OUT;
	if (data->scale_zoom < 0.1f)
		data->scale_zoom = 0.1f;
	if (data->scale_zoom > 10.0f)
		data->scale_zoom = 10.0f;
}
void	calculate_new_position(t_w_data *data, int i, int j, float cx, float cy)
{
	data->p[i][j].x = (data->p_b[i][j].x - cx) * data->scale_zoom + cx;
	data->p[i][j].y = (data->p_b[i][j].y - cy) * data->scale_zoom + cy;
}
void	zoom(int key, t_w_data *data)
{
	float	center_x;
	float	center_y;
	int		i;
	int		j;

	update_scale_zoom(key, data);
	center_x = (float)data->window_w / 2.0f;
	center_y = (float)data->window_h / 2.0f;
	i = -1;
	while (++i < data->grid->rows)
	{
		j = -1;
		while (++j < data->grid->cols)
		{
			calculate_new_position(data, i, j, center_x, center_y);
		}
	}
} */
