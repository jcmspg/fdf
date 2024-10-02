/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:56:44 by joao              #+#    #+#             */
/*   Updated: 2024/10/02 16:46:13 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pan(int key, t_w_data *data)
{
	move(key, data);
	update_img(data);
	draw_gui(data);
}

void	rotate(int key, t_w_data *data)
{
	if (key == Q || key == E)
	{
		rotate_x_key(key, data);
		rotate_x(data);
	}
	if (key == A || key == D)
	{
		rotate_y_key(key, data);
		rotate_y(data);
	}
	if (key == W || key == S)
	{
		rotate_z_key(key, data);
		rotate_z(data);
	}
	update_img(data);
	draw_gui(data);
}

void	fly_conic(int key, t_w_data *data)
{
	if (key == W || key == S)
		change_aero(key, data);
	if (key == A || key == D)
		change_focal_d(key, data);
}

void	change_focus(int key, t_w_data *data)
{
	fly_conic(key, data);
	update_img(data);
	draw_gui(data);
}

void	zoom_in_out(int key, t_w_data *data)
{
	zoom(key, data);
	update_img(data);
	draw_gui(data);
}
