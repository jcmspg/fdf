/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:38:00 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:53:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	calculate_new_coordinates_fp(t_f_point *point, float cos_angle,
	float sin_angle, t_w_data *data)
{
	float	x;
	float	y;
	float	z;
	float	x_new;
	float	z_new;

	x = point->x - data->window_w / 2.0f;
	y = point->y - data->window_h / 2.0f;
	z = point->z;
	x_new = x * cos_angle + z * sin_angle;
	z_new = -x * sin_angle + z * cos_angle;
	point->x = x_new + data->window_w / 2.0f;
	point->y = y + data->window_h / 2.0f;
	point->z = z_new;
}

static void	rotate_grid(t_w_data *data, float cos_angle, float sin_angle)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			calculate_new_coordinates_fp(&data->p_b[i][j],
				cos_angle, sin_angle, data);
			j++;
		}
		i++;
	}
}

void	orbit(t_w_data *data)
{
	float	angle_x;
	float	cos_angle;
	float	sin_angle;

	angle_x = degree_to_radian(data->angle);
	cos_angle = cos(angle_x);
	sin_angle = sin(angle_x);
	rotate_grid(data, cos_angle, sin_angle);
}
