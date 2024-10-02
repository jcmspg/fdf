/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:53:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:56:58 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	calculate_tilt_coordinates(t_f_point *point, float cos_angle,
	float sin_angle, t_w_data *data)
{
	float	x;
	float	y;
	float	z;
	float	y_new;
	float	z_new;

	x = point->x - data->window_w / 2.0f;
	y = point->y - data->window_h / 2.0f;
	z = point->z;
	y_new = y * cos_angle - z * sin_angle;
	z_new = y * sin_angle + z * cos_angle;
	point->x = x + data->window_w / 2.0f;
	point->y = y_new + data->window_h / 2.0f;
	point->z = z_new;
}

static void	tilt_grid(t_w_data *data, float cos_angle, float sin_angle)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			calculate_tilt_coordinates(&data->p_b[i][j],
				cos_angle, sin_angle, data);
			j++;
		}
		i++;
	}
}

void	change_tilt(t_w_data *data)
{
	float	angle_y;
	float	cos_angle;
	float	sin_angle;

	angle_y = degree_to_radian(data->angle);
	cos_angle = cos(angle_y);
	sin_angle = sin(angle_y);
	tilt_grid(data, cos_angle, sin_angle);
}
