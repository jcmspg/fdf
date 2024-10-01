/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 02:50:42 by joao              #+#    #+#             */
/*   Updated: 2024/10/01 20:34:00 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_help2(t_w_data *data, int pos)
{
	mlx_string_put(data->mlx, data->win, pos - 100, pos - 50, WHITE,
		"Welcome to FDF");
	mlx_string_put(data->mlx, data->win, pos - 100, pos, WHITE,
		"Use the following keys to navigate:");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 20, WHITE,
		"WASD - Move");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 80, WHITE,
		"WS - Rotate X");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 40, WHITE,
		"QE - Rotate Y");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 60, WHITE,
		"AD - Rotate Z");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 100, WHITE,
		"C - Change color mode");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 120, WHITE,
		"P - Pan");
}

void	show_help3(t_w_data *data, int author_x, int author_y, int pos)
{
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 140, WHITE,
		"Z - Zoom");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 160, WHITE,
		"T - Height (BETA WIP)");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 180, WHITE,
		"F - Reset");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 200, WHITE,
		"H - Help");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 220, WHITE,
		"ESC - Exit");
	mlx_string_put(data->mlx, data->win, pos - 100, pos + 240, WHITE,
		"Change mode to exit help");
	mlx_string_put(data->mlx, data->win, author_x, author_y, WHITE,
		"joamiran");
}

void	show_help(t_w_data *data)
{
	int	author_x;
	int	author_y;
	int	pos;

	pos = data->window_w / 2;
	author_y = data->window_h - 20;
	author_x = data->window_w - 100;
	clear_image(data);
	make_image(data);
	show_help2(data, pos);
	show_help3(data, author_x, author_y, pos);
}

// function to show an intro screen with brief description of the program
void	intro_screen(t_w_data *data)
{
	int	pos_w;
	int	pos_h;
	int	author_x;
	int	author_y;

	author_x = data->window_w - 100;
	author_y = data->window_h - 20;
	pos_w = data->window_w / 2;
	pos_h = data->window_h / 2;
	clear_image(data);
	make_image(data);
	mlx_string_put(data->mlx, data->win, pos_w - 100, pos_h - 50, WHITE,
		"Welcome to FDF");
	mlx_string_put(data->mlx, data->win, pos_w - 100, pos_h, WHITE,
		"Press H for help");
	mlx_string_put(data->mlx, data->win, pos_w - 100, pos_h + 20, WHITE,
		"Press ESC to exit");
	mlx_string_put(data->mlx, data->win, pos_w - 100, pos_h + 40, WHITE,
		"Press SPACE to continue");
	mlx_string_put(data->mlx, data->win, author_x, author_y, WHITE,
		"joamiran");
}
