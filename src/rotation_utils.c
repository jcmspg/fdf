/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 21:58:51 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_angle(t_w_data *data)
{
	data->angle = ANGLE_VALUE;
	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;
	data->radius = 100;
}

void	rotate_z_key(int key, t_w_data *data)
{
	if (key == W)
	{
		data->angle = ANGLE_VALUE;
		data->angle_z += ANGLE_VALUE;
	}
	if (key == S)
	{
		data->angle = -ANGLE_VALUE;
		data->angle_z -= ANGLE_VALUE;
	}
	transform_p(data);
}

void	rotate_y_key(int key, t_w_data *data)
{
	if (key == A)
	{
		data->angle = -ANGLE_VALUE;
		data->angle_y -= ANGLE_VALUE;
	}
	if (key == D)
	{
		data->angle = ANGLE_VALUE;
		data->angle_y += ANGLE_VALUE;
	}
	transform_p(data);
}

void	rotate_x_key(int key, t_w_data *data)
{
	if (key == Q)
	{
		data->angle = -ANGLE_VALUE;
		data->angle_x -= ANGLE_VALUE;
	}
	if (key == E)
	{
		data->angle = ANGLE_VALUE;
		data->angle_x += ANGLE_VALUE;
	}
	transform_p(data);
}
