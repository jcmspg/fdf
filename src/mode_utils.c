/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:56:44 by joao              #+#    #+#             */
/*   Updated: 2024/09/11 20:38:41 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void pan(int key, w_data *data)
{
	move(key, data);
	update_img(data);
	draw_gui(data);
}

void rotate(int key, w_data *data)
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

void fly_conic(int key, w_data *data)
{
	if (key == W || key == S)
		change_aero(key, data);
	if (key == A || key == D)
		change_focal_d(key, data);
}

void change_focus(int key, w_data *data)
{
	fly_conic(key, data);
	update_img(data);
	draw_gui(data);
}
void zoom_in_out(int key, w_data *data)
{
	zoom(key, data);
	update_img(data);
	draw_gui(data);
}

void reset(w_data *data)
{
	init_angle(data);
	restore_origin(data);
	build_model(data);
	update_img(data);
	draw_gui(data);
	data->current_mode = &data->modes[0];
}


void color(int key, w_data *data)
{
	color_mode(data);
	cycle_color_mode(key, data);
	update_img(data);
	draw_gui(data);
}

void display_help(int key, w_data *data)
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

void change_mode(int key, w_data *data)
{
	if (key == SPACE)
	{
		data->current_mode = &data->modes[0];
		clear_image(data);
		build_model(data);
		backup_data(data);
		make_image(data);
		draw_gui(data);
	}
	else if(key == H)
	{
		display_help(key, data);
	}
	else if (key == I)
	{
		data->current_mode = &data->modes[0];
		clear_image(data);
		build_model(data);
		backup_data(data);
		make_image(data);
		draw_gui(data);
	}
	else if (key == G)
	{
		data->current_mode = &data->modes[1];
		pcoords_spherical(data);
		build_sphere(data);
		draw_gui(data);
	}
	else if (key ==C)
	{
		data->current_mode = &data->modes[2];
		build_conic(data);
		change_focus(key, data);
	}
	else if (key == ESC)
		close_window(data);
	else if(key == F)
		reset(data);
	else if (key == C)
		color(key, data);
}

void handle_interaction(int key, w_data *data)
{
	//call the appropriate function based on mode
	if (key == P && data->current_mode->pan != NULL)
	{
		data->current_mode = pan;
		printf ("CALLING PAN \n");
		data->current_mode->pan(key, data);
	}
	if (key == R && data->current_mode->rotate != NULL)
		{
			data->current_mode = rotate;
			printf("CALLING ROTATE \n");
			data->current_mode->rotate(key, data);
		}
	if (key == Z && data->current_mode->zoom != NULL)
	{
		printf("calling ZOOM");
		data->current_mode->zoom(key, data);
	}
	
	if (key == O && data->current_mode->orbit != NULL)
		data->current_mode->orbit(key, data);

	if (key == W )
		data->current_mode->fun(key, data);
}

int key_handle(int key, w_data *data)
{
	// handle the mode switch
	change_mode(key, data);

	// handle mode specific interactions
	handle_interaction(key, data);

	return 0;
}

