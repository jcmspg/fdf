/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:52:56 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 20:58:09 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_point_x(t_f_point *point, t_rotation_data *rot_data)
{
	float	y;
	float	new_y;
	float	new_z;

	y = point->y - rot_data->center_y;
	new_y = y * rot_data->cos_angle - point->z * rot_data->sin_angle;
	new_z = y * rot_data->sin_angle + point->z * rot_data->cos_angle;
	point->y = new_y + rot_data->center_y;
	point->z = new_z;
}

static void	rotate_row_x(t_w_data *data, int row, t_rotation_data *rot_data)
{
	int	j;

	j = 0;
	while (j < data->grid->cols)
	{
		rotate_point_x(&data->p_b[row][j], rot_data);
		j++;
	}
}

void	rotate_x(t_w_data *data)
{
	t_rotation_data	rot_data;
	int				i;

	rot_data.cos_angle = cos(degree_to_radian(data->angle));
	rot_data.sin_angle = sin(degree_to_radian(data->angle));
	rot_data.center_y = data->window_h / 2;
	i = 0;
	while (i < data->grid->rows)
	{
		rotate_row_x(data, i, &rot_data);
		i++;
	}
	apply_zoom(data);
}
