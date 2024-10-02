/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:16:41 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:58:56 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_orbit(int key, t_w_data *data)
{
	if (key == A)
	{
		data->angle = -ANGLE_VALUE;
		data->angle_x -= ANGLE_VALUE;
	}
	else if (key == D)
	{
		data->angle = ANGLE_VALUE;
		data->angle_x += ANGLE_VALUE;
	}
	orbit(data);
}

static void	handle_tilt(int key, t_w_data *data)
{
	if (key == Q)
	{
		data->angle = -ANGLE_VALUE;
		data->angle_y -= ANGLE_VALUE;
	}
	else if (key == E)
	{
		data->angle = ANGLE_VALUE;
		data->angle_y += ANGLE_VALUE;
	}
	change_tilt(data);
}

void	ro_sphere(int key, t_w_data *data)
{
	if (key == A || key == D)
	{
		handle_orbit(key, data);
	}
	else if (key == Q || key == E)
	{
		handle_tilt(key, data);
	}
	apply_zoom(data);
	update_img(data);
	draw_gui(data);
}

void	build_sphere(t_w_data *data)
{
	clear_image(data);
	pcoords_spherical(data);
	apply_zoom(data);
	color_mode(data);
	draw_poly(data);
	make_image(data);
}
