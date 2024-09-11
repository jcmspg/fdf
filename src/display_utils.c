/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:11:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/11 20:44:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Data functionsd

// free lookup tables
void free_lookup(w_data *data)
{
	if (data->lookup != NULL)
	{
		if (data->lookup->sin_table != NULL)
			free(data->lookup->sin_table);
		if (data->lookup->cos_table != NULL)
			free(data->lookup->cos_table);
		free(data->lookup);
	}
}

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

void free_fpoints(f_point **points)
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
		free_fpoints(data->points_backup);
	if (data->points_restore != NULL)
		free_fpoints(data->points_restore);
}

void free_data(w_data *data)
{
	free_all_points(data);
	
	free_lookup(data);

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

	// display information related to the program
	int info_x = x_left;
	int info_y = y;
	mlx_string_put(data->mlx, data->win, info_x, info_y, text_color, "Welcome to FDF");

	// file path
	mlx_string_put(data->mlx, data->win, info_x, info_y + line_spacing, text_color, "File: ");
	mlx_string_put(data->mlx, data->win, info_x + 30, info_y + line_spacing, text_color, data->file);

	// grid size rows and cols
	mlx_string_put(data->mlx, data->win, info_x, info_y + 2 * line_spacing, text_color, "Rows: ");
	mlx_string_put(data->mlx, data->win, info_x + 40, info_y + 2 * line_spacing, text_color, ft_itoa(data->grid->rows));
	mlx_string_put(data->mlx, data->win, info_x, info_y + 3 * line_spacing, text_color, "Cols: ");
	mlx_string_put(data->mlx, data->win, info_x + 40, info_y + 3 * line_spacing, text_color, ft_itoa(data->grid->cols));
	
	
	// max and min z values
	mlx_string_put(data->mlx, data->win, info_x, info_y + 5 * line_spacing, text_color, "Max Z: ");
	mlx_string_put(data->mlx, data->win, info_x + 50, info_y + 5 * line_spacing, text_color, ft_itoa(data->max_z));

	mlx_string_put(data->mlx, data->win, info_x, info_y + 6 * line_spacing, text_color, "Min Z: ");
	mlx_string_put(data->mlx, data->win, info_x + 50, info_y + 6 * line_spacing, text_color, ft_itoa(data->min_z));

	// zooooom
	mlx_string_put(data->mlx, data->win, info_x, info_y + 7 * line_spacing, text_color, "Zoom: ");
	mlx_string_put(data->mlx, data->win, info_x + 50, info_y + 7 * line_spacing, text_color, ft_itoa(data->scale));
	
	// rotation values
	mlx_string_put(data->mlx, data->win, info_x, info_y + 8 * line_spacing, text_color, "Angle X: ");
	mlx_string_put(data->mlx, data->win, info_x + 70, info_y + 8 * line_spacing, text_color, ft_itoa(data->angle_x));
	mlx_string_put(data->mlx, data->win, info_x, info_y + 9 * line_spacing, text_color, "Angle Y: ");
	mlx_string_put(data->mlx, data->win, info_x + 70, info_y + 9 * line_spacing, text_color, ft_itoa(data->angle_y));
	mlx_string_put(data->mlx, data->win, info_x, info_y + 10 * line_spacing, text_color, "Angle Z: ");
	mlx_string_put(data->mlx, data->win, info_x + 70, info_y + 10 * line_spacing, text_color, ft_itoa(data->angle_z));
	

	mlx_string_put(data->mlx, data->win, info_x, info_y + 12 * line_spacing, text_color, "H - Help");
	mlx_string_put(data->mlx, data->win, info_x, info_y + 13 * line_spacing, text_color, "ESC - Exit");

    // Display the author's name
    int author_x = data->window_width - 100; // Right aligned
    int author_y = data->window_height - 20; // Bottom aligned
    mlx_string_put(data->mlx, data->win, author_x, author_y, text_color, "joamiran");
}

void make_image(w_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
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

void cycle_color_mode(int key, w_data *data)
{
	if (key == C)
	{
		data->color_mode++;
		if (data->color_mode > 2)
			data->color_mode = 0;
	}
}
