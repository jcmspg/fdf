/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:56:44 by joao              #+#    #+#             */
/*   Updated: 2024/09/03 21:00:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to to assign mode to the program
void change_mode(int key, w_data *data)
{
	if (key == P)
		data->mode = Pan;
	if (key == R)
		data->mode = Rotate;
	if (key == Z)
		data->mode = Zoom;
	if (key == H)
		data->mode = Help;
	if (key == C)
		data->mode = Color;
	if (key == T)
		data->mode = Height;
	if (key == F)
		data->mode = Reset;
	if (key == I)
		data->mode = Conic;
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
	// print the z coordinates of the points
	for (int i = 0; i < data->grid->rows; i++)
	{
		for (int j = 0; j < data->grid->cols; j++)
		{
			printf("z: %d\n", data->points[i][j].z);
		}
	}
}

void fly_conic(int key, w_data *data)
{
	if (key == W || key == S)
		change_tilt(key, data);
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
}

int key_handle(int key, w_data *data)
{
	if (key == ESC)
		close_window(data);
	if (key == SPACE && data->mode == idle)
	{
		data->mode = Iso;
		build_model(data);
		backup_data(data);
		make_image(data);
		draw_gui(data);
	}
	change_mode(key, data);
	if (data->mode == Pan)
		pan(key, data);
	if (data->mode == Rotate)
		rotate(key, data);
	if (data->mode == Zoom)
		zoom_in_out(key, data);
	if (data->mode == Reset)
		reset(data);
	if (data->mode == Height)
		height(key, data);
	if (data->mode == Color)
		color(key, data);
	if (data->mode == Help)
		display_help(key, data);
	if (data->mode == Conic)
	{
		build_conic(data);
		change_focus(key, data);
	}
	return (0);
}
