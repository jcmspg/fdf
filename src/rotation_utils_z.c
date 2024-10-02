/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils_z.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:00:53 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 21:02:21 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_point_z(t_f_point *point, t_rotation_z_data *rot_data)
{
	float	x;
	float	y;
	float	new_x;
	float	new_y;

	x = point->x - rot_data->center_x;
	y = point->y - rot_data->center_y;
	new_x = x * rot_data->cos_angle - y * rot_data->sin_angle;
	new_y = x * rot_data->sin_angle + y * rot_data->cos_angle;
	point->x = new_x + rot_data->center_x;
	point->y = new_y + rot_data->center_y;
}

static void	rotate_row_z(t_w_data *data, int row, t_rotation_z_data *rot_data)
{
	int	j;

	j = 0;
	while (j < data->grid->cols)
	{
		rotate_point_z(&data->p_b[row][j], rot_data);
		j++;
	}
}

void	rotate_z(t_w_data *data)
{
	t_rotation_z_data	rot_data;
	int					i;

	rot_data.cos_angle = cos(degree_to_radian(data->angle));
	rot_data.sin_angle = sin(degree_to_radian(data->angle));
	rot_data.center_x = data->window_w / 2;
	rot_data.center_y = data->window_h / 2;
	i = 0;
	while (i < data->grid->rows)
	{
		rotate_row_z(data, i, &rot_data);
		i++;
	}
	apply_zoom(data);
}
