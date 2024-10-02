/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:43:50 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 20:49:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset(t_w_data *data)
{
	data->scale_zoom = 1;
	init_angle(data);
	restore_origin(data);
	build_model(data);
	update_img(data);
	draw_gui(data);
	data->mode = 'i';
}

void	color(int key, t_w_data *data)
{
	color_mode(data);
	cycle_color_mode(key, data);
	update_img(data);
	draw_gui(data);
}

void	display_help(int key, t_w_data *data)
{
	if (key == H)
		show_help(data);
	if (key == SPACE)
		intro_screen(data);
}
