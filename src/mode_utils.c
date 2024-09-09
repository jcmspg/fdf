/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:56:44 by joao              #+#    #+#             */
/*   Updated: 2024/09/09 18:02:46 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to to assign mode to the program
void change_mode(int key, w_data *data)
{
	if (key == P)
		data->mode = Pan;
	if (key == R && data->mode != Conic && data->mode != Spherical)
		data->mode = Rotate;
	if (key == Z)
		data->mode = Zoom;
	if (key == H)
		data->mode = Help;
	if (key == C)
		data->mode = Color;
	if (key == T && data->mode != Conic && data->mode != Spherical)
		data->mode = Height;
	if (key == F)
		data->mode = Reset;
	if (key == I)
		data->mode = Conic;
	if (key == G)
		data->mode = Spherical;
	if (key == O)
		data->mode = Orbit;
}

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
	update_img(data);
	draw_gui(data);
}

void height(int key, w_data *data)
{
	scale_z(key, data);
	z_assign(data);
	z_assign_backup(data);
	update_img(data);
	draw_gui(data);
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

int key_handle(int key, w_data *data)
{
	if (key == ESC)
		close_window(data);
	if (key == SPACE && data->mode == idle)
	{
		data->mode = Iso;
		build_model(data);
		make_image(data);
		draw_gui(data);
	}
	change_mode(key, data);
	if (data->mode == Pan && data->mode != idle)
		pan(key, data);
	if (data->mode == Rotate && data->mode != idle)
		rotate(key, data);
	if (data->mode == Zoom && data->mode != idle)
		zoom_in_out(key, data);
	if (data->mode == Reset && data->mode != idle)
		reset(data);
	if (data->mode == Height && data->mode != idle)
		height(key, data);
	if (data->mode == Color && data->mode != idle)
		color(key, data);
	if (data->mode == Help && data->mode != idle)
		display_help(key, data);
	if (data->mode == Conic && data->mode != idle)
	{
		build_conic(data);
		change_focus(key, data);
	}
	if (data->mode == Spherical && data->mode != idle)
	{
		pcoords_spherical(data);
		build_sphere(data);
		draw_gui(data);
	}
	if (data->mode == Orbit && data->mode != idle)
		{
			ro_sphere(key, data);
		}
	return (0);
}
