/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:11:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/30 04:31:40 by joao             ###   ########.fr       */
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
    int x_left = data->window_width * 0.05; // 5% from the left
    int y = data->window_height * 0.1; // 10% from the top
    int text_color = 0xFFFFFF; // Example color
    int line_spacing = 15; // Tighter line spacing

    // Display ASCII art
    int ascii_art_x = data->window_width - 200; // Right aligned
    int ascii_art_y = y;
    mlx_string_put(data->mlx, data->win, ascii_art_x, ascii_art_y, text_color, "  _____  ____  _____ ");
    mlx_string_put(data->mlx, data->win, ascii_art_x, ascii_art_y + line_spacing, text_color, " |  ___||  _ \\|  ___|");
    mlx_string_put(data->mlx, data->win, ascii_art_x, ascii_art_y + 2 * line_spacing, text_color, " | |_   | | | | |_   ");
    mlx_string_put(data->mlx, data->win, ascii_art_x, ascii_art_y + 3 * line_spacing, text_color, " |  _|  | |_| |  _|  ");
    mlx_string_put(data->mlx, data->win, ascii_art_x, ascii_art_y + 4 * line_spacing, text_color, " |_|    |_____|_| ");

    // Display the scale factor
    char scale_factor[50];
    sprintf(scale_factor, "%.2f", data->scale);
    mlx_string_put(data->mlx, data->win, x_left, y, text_color, "Scale:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y, text_color, scale_factor);

    // Display the highest z value
    char highest_z[50];
    sprintf(highest_z, "%d", data->max_z);
    mlx_string_put(data->mlx, data->win, x_left, y + line_spacing, text_color, "Max Z:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y + line_spacing, text_color, highest_z);

    // Display the lowest z value
    char lowest_z[50];
    sprintf(lowest_z, "%d", data->min_z);
    mlx_string_put(data->mlx, data->win, x_left, y + 2 * line_spacing, text_color, "Min Z:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y + 2 * line_spacing, text_color, lowest_z);

    // Display the zoom factor
    char zoom_factor[50];
    sprintf(zoom_factor, "%.2f", data->scale);
    mlx_string_put(data->mlx, data->win, x_left, y + 3 * line_spacing, text_color, "Zoom:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y + 3 * line_spacing, text_color, zoom_factor);

    // Display the color mode
    char color_mode[50];
    sprintf(color_mode, "%d", data->color_mode);
    mlx_string_put(data->mlx, data->win, x_left, y + 4 * line_spacing, text_color, "Color:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y + 4 * line_spacing, text_color, color_mode);

    // Display the file name
    mlx_string_put(data->mlx, data->win, x_left, y + 5 * line_spacing, text_color, "File:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y + 5 * line_spacing, text_color, data->file);

    // Display the window size
    char window_size[50];
    sprintf(window_size, "%dx%d", data->window_width, data->window_height);
    mlx_string_put(data->mlx, data->win, x_left, y + 6 * line_spacing, text_color, "Window:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y + 6 * line_spacing, text_color, window_size);

    // Display the grid size
    char grid_size[50];
    sprintf(grid_size, "%dx%d", data->grid->rows, data->grid->cols);
    mlx_string_put(data->mlx, data->win, x_left, y + 7 * line_spacing, text_color, "Grid:");
    mlx_string_put(data->mlx, data->win, x_left + 50, y + 7 * line_spacing, text_color, grid_size);

    // Display the author's name
    int author_x = data->window_width - 100; // Right aligned
    int author_y = data->window_height - 20; // Bottom aligned
    mlx_string_put(data->mlx, data->win, author_x, author_y, text_color, "joamiran");
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
	color_mode(data);
	draw_poly(data);
	make_image(data);
}
// Key functions

void cycle_color_mode(int key, w_data *data)
{
	if (key == C)
	{
		data->color_mode++;
		if (data->color_mode > 2)
			data->color_mode = 0;
	}
}

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
		cycle_color_mode(key, data);
		update_img(data);
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
	if (key == LEFT || key == RIGHT)
	{
		scale_z(key, data);
		z_assign(data);
		z_assign_backup(data);
		update_img(data);
		draw_gui(data);
	}
	return 0;
}

