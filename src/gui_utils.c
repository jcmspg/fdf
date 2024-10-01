/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:06:17 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 19:40:25 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_ascii_art(t_w_data *data, int x, int y, int text_color)
{
	int	line_spacing;

	line_spacing = 15;
	mlx_string_put(data->mlx, data->win, x, y,
		text_color, "  _____  ____  _____ ");
	mlx_string_put(data->mlx, data->win, x, y + line_spacing, text_color,
		" |  ___||  _ \\|  ___|");
	mlx_string_put(data->mlx, data->win, x, y + 2 * line_spacing, text_color,
		" | |_   | | | | |_   ");
	mlx_string_put(data->mlx, data->win, x, y + 3 * line_spacing, text_color,
		" |  _|  | |_| |  _|  ");
	mlx_string_put(data->mlx, data->win, x, y + 4 * line_spacing, text_color,
		" |_|    |_____|_| ");
}

void	draw_author(t_w_data *data, int x, int y, int text_color)
{
	mlx_string_put(data->mlx, data->win, x, y, text_color, "joamiran");
}

void	draw_gui(t_w_data *data)
{
	int	x_left;
	int	y;
	int	author_x;
	int	author_y;
	int	ascii_art_x;

	ascii_art_x = data->window_w - 200;
	x_left = data->window_w * 0.05;
	y = data->window_h * 0.1;
	draw_ascii_art(data, ascii_art_x, y, data->text_color);
	draw_information(data);
	author_x = data->window_w - 100;
	author_y = data->window_h - 20;
	draw_author(data, author_x, author_y, data->text_color);
}
