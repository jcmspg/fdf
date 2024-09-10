/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:56:44 by joao              #+#    #+#             */
/*   Updated: 2024/09/10 21:25:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void change_interaction(int key, w_data *data)
{
	if (key == P)
		data->interact = Pan;
	if (data->mode != Spherical && data->mode != Conic)
	{
		if (key == R)
			data->interact = Rotate;
	}
	if (key == Z)
		data->interact = Zoom;
	if (data->mode == Spherical)
	{
		if (key == O)
			data->interact = Orbit;
	}
}



// function to to assign mode to the program
void change_mode(int key, w_data *data)
{
	if (key == H)
		data->mode = Help;
	if (key == C)
		data->mode = Color;
/* 	if (key == T && data->mode != Conic && data->mode != Spherical)
		data->mode = Height; */
	if (key == F)
		data->mode = Reset;
	if (key == I)
		data->mode = Conic;
	if (key == G)
		data->mode = Spherical;
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
//	pcoords_iso(data);
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
}

/* void height(int key, w_data *data)
{
	scale_z(key, data);
	z_assign(data);
	z_assign_backup(data);
	update_img(data);
	draw_gui(data);
} */
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

int key_handle_mode(int key, w_data *data)
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
	
	
	
	if (data->mode == Reset && data->mode != idle)
		reset(data);

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

	return (0);
}

int key_handle_interact(int key, w_data *data)
{
	change_interaction(key, data);
	
	if (data->interact == Pan )
		pan(key, data);
	if (data->interact == Rotate)
		rotate(key, data);
	if (data->interact == Zoom)
		zoom_in_out(key, data);
	if (data->interact == Orbit)
		ro_sphere(key, data);
	return (0);
}

int key_handle(int key, w_data *data)
{
	key_handle_mode(key, data);
	key_handle_interact(key, data);
	return (0);
}
