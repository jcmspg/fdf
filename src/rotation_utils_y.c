/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils_y.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:58:24 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 21:00:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	rotate_point_y(t_f_point *point, t_rotation_y_data *rot_data)
{
	float	x;
	float	new_x;
	float	new_z;

	x = point->x - rot_data->center_x;
	new_x = x * rot_data->cos_angle + point->z * rot_data->sin_angle;
	new_z = -x * rot_data->sin_angle + point->z * rot_data->cos_angle;
	point->x = new_x + rot_data->center_x;
	point->z = new_z;
}

static void	rotate_row_y(t_w_data *data, int row, t_rotation_y_data *rot_data)
{
	int	j;

	j = 0;
	while (j < data->grid->cols)
	{
		rotate_point_y(&data->p_b[row][j], rot_data);
		j++;
	}
}

void	rotate_y(t_w_data *data)
{
	t_rotation_y_data	rot_data;
	int					i;

	rot_data.cos_angle = cos(degree_to_radian(data->angle));
	rot_data.sin_angle = sin(degree_to_radian(data->angle));
	rot_data.center_x = data->window_w / 2;
	i = 0;
	while (i < data->grid->rows)
	{
		rotate_row_y(data, i, &rot_data);
		i++;
	}
	apply_zoom(data);
}
