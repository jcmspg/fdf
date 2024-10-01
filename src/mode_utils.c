/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:56:44 by joao              #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void pan(int key, t_w_data *data)
{
	move(key, data);
	update_img(data);
	draw_gui(data);
}

void rotate(int key, t_w_data *data)
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
	//	pcoords_iso(data);
	update_img(data);
	draw_gui(data);
}

void fly_conic(int key, t_w_data *data)
{
	if (key == W || key == S)
		change_aero(key, data);
	if (key == A || key == D)
		change_focal_d(key, data);
}

void change_focus(int key, t_w_data *data)
{
	fly_conic(key, data);
	update_img(data);
	draw_gui(data);
}
void zoom_in_out(int key, t_w_data *data)
{
	zoom(key, data);
	update_img(data);
	draw_gui(data);
}

void reset(t_w_data *data)
{
	init_angle(data);
	restore_origin(data);
	build_model(data);
	update_img(data);
	draw_gui(data);
	data->mode = 'i';
}


void color(int key, t_w_data *data)
{
	color_mode(data);
	cycle_color_mode(key, data);
	update_img(data);
	draw_gui(data);
}

void display_help(int key, t_w_data *data)
{
	if (key == H)
	{
		show_help(data);
	}
	if (key == SPACE)
	{
		intro_screen(data);
	}
}

void change_mode(int key, t_w_data *data)
{
	if (key == SPACE && !data->mode)
	{
		data->mode = 'i';
		backup_data(data);
		clear_image(data);
		build_model(data);
		change_backup(data);
		make_image(data);
		draw_gui(data);
	}
	else if(key == H)
	{
		display_help(key, data);
	}
	else if (key == I && data->mode != 'i')
	{
		data->mode = 'i';
		clear_image(data);
		build_model(data);
		change_backup(data);
		make_image(data);
		draw_gui(data);
	}
	else if (key == G)
	{
		data->mode = 'g';
		//pcoords_spherical(data);
		build_sphere(data);
		draw_gui(data);
	}
	else if (key == N)
	{
		data->mode = 'c';
		build_conic(data);
		draw_gui(data);
	}
	else if (key == ESC)
		close_window(data);
	else if(key == F)
		reset(data);
	else if (key == C)
		color(key, data);
}

void handle_interaction(int key, t_w_data *data)
{
	//call the appropriate function based on mode
	if (key == P)
	{
		data->interaction = 'p';

	}

	if (key == R && data->mode != 'g')
		{
			data->interaction = 'r';

		}
	if (key == Z)
	{
		data->interaction = 'z';
	}

	if (key == O && data->mode == 'g')
	{
		data->interaction = 'o';
	}

}

void interaction_functions(int key, t_w_data *data)
{
	if (key == W || key == S || key == A || key == D || key == Q || key == E)
	{
		if (data->interaction == 'p')
			pan(key, data);
		if (data->interaction == 'r')
			rotate(key, data);
		if (data->interaction == 'z')
			zoom_in_out(key, data);
		if (data->interaction == 'o' && data->mode == 'g')
			ro_sphere(key, data);
		if (data->interaction == 'o' && data->mode == 'c')
			change_focus(key, data);
	}
}



int key_handle(int key, t_w_data *data)
{
	if (key == N || key == I || key == C || key == G || key == ESC || key == F || key == SPACE || key == H)
	// handle the mode switch
		change_mode(key, data);
	if (key == P || key == O || key == Z || key == R)
	// handle mode specific interactions
		handle_interaction(key, data);
	if (key == W || key == S || key == A || key == D || key == Q || key == E)
	// functions to IMPLEMENT interaction
		interaction_functions(key, data);

	return 0;
}
