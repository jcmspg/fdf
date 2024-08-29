/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:11:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/29 21:07:22 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Data functions

// free t_points
void free_points(t_point **points)
{
	int i = 0;
	while (points[i] != NULL)
	{
		free(points[i]);
		i++;
	}
	free(points);
}
//free all the points
void free_all_points(w_data *data)
{
	if (data->points != NULL)
		free_points(data->points);
	if (data->points_backup != NULL)
		free_points(data->points_backup);
	if (data->points_restore != NULL)
		free_points(data->points_restore);
}

void free_data(w_data *data)
{
	free_all_points(data);

	if (data->grid != NULL)
		free(data->grid);

	if (data->img.img != NULL)
		mlx_destroy_image(data->mlx, data->img.img);

	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);

	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int close_window(w_data *data)
{
	free_data(data);
	exit(0);
}

// Image functions

// mlx initialization and checks
void *init_mlx(void)
{
	void *mlx;

	mlx = mlx_init();
	if (!mlx)
	{
		fprintf(stderr, "Error initializing mlx\n");
		return NULL;
	}
	return mlx;
}

// create a new Window
void create_window(w_data *data)
{
	data->win = mlx_new_window(data->mlx, data->window_width, data->window_height, data->title);
	if (!data)
	{
		fprintf(stderr, "Error creating window\n");
		return;
	}
}

// Create a new image
void create_image(w_data *data)
{
	data->img.img = mlx_new_image(data->mlx, data->window_width, data->window_height);
	if (!data->img.img)
	{
		fprintf(stderr, "Error creating image\n");
		return;
	}
	data->img.address = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	if (!data->img.address)
	{
		fprintf(stderr, "Error getting image address\n");
		return;
	}
}

void draw_gui(w_data *data)
{

	// display window size and grid size
	// display the arg[1]
	mlx_string_put(data->mlx, data->win, 600, 580, 0x00FFFFFF, "File:");
	// just the file name
	mlx_string_put(data->mlx, data->win, 600, 600, 0x00FFFFFF, data->file);
	mlx_string_put(data->mlx, data->win, 600, 620, 0x00FFFFFF, "window size:");
/*	char *s1 = ft_itoa(data->window_width);
	char *s2 = ft_itoa(data->window_height);
	char *s4 = ft_itoa(data->grid->rows);
	char *s5 = ft_itoa(data->grid->cols);
	char *s3 = ft_strjoin(ft_strjoin(str, " X "), str2);
	char *s6 = ft_strjoin(ft_strjoin(s4, " X "), s5);
	mlx_string_put(data->mlx, data->win, 600, 640, 0x00FFFFFF, s3);
	mlx_string_put(data->mlx, data->win, 600, 680, 0x00FFFFFF, "grid size:");
	mlx_string_put(data->mlx, data->win, 600, 700, 0x00FFFFFF, s6);

	// free the strings
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
    free(s6);

	//free_pointers(s3, s6, s1, s2, s4, s5, NULL);*/
}

void make_image(w_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_gui(data);
}

// clear the image
void clear_image(w_data *data)
{
	int x;
	int y;

	y = 0;

	while (y < data->window_height)
	{
		x = 0;
		while (x < data->window_width)
		{
			my_mlx_pixel_put(data, x, y, BACKGROUND);
			x++;
		}
		y++;
	}
}

// draw the updated image
void update_img(w_data *data)
{
	clear_image(data);
	draw_poly(data);
	make_image(data);
}
// Key functions

int key_handle(int key, w_data *data)
{
	if (key == ESC)
		close_window(data);
	if (key == W || key == A || key == S || key == D)
	{
		move(key, data);
		update_img(data);
		draw_gui(data);
	}
	if (key == C)
	{
		clear_image(data);
		make_image(data);
		draw_gui(data);
	}
	if (key == R)
	{
		restore_origin(data);
		update_img(data);
		draw_gui(data);
	}
	if (key == UP || key == DOWN)
	{
		zoom(key, data);
		update_img(data);
		draw_gui(data);
	}
	return 0;
}
