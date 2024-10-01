/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:49:00 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 20:43:30 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_string_with_offset(t_w_data *data, int x, int y, char *string)
{
	mlx_string_put(data->mlx, data->win, x, y, data->text_color, string);
}

void	draw_static_text(t_w_data *data, int x_left, int y, int line_spacing)
{
	put_string_with_offset(data, x_left, y, "Welcome to FDF");
	put_string_with_offset(data, x_left, y + line_spacing, "File: ");
	put_string_with_offset(data, x_left + 30, y + line_spacing, data->file);
}

void	draw_dynamic_value(t_w_data *data, int x_left, int y, float value)
{
	char	*value_str;

	value_str = ft_itoa(value);
	if (value_str)
	{
		put_string_with_offset(data, x_left + 80, y, value_str);
		free(value_str);
	}
}

void	draw_dynamic_values(t_w_data *data, int x_left, int y, int line_spacing)
{
	put_string_with_offset(data, x_left, y, "rows:");
	draw_dynamic_value(data, x_left, y + 2 * line_spacing, data->grid->rows);
	put_string_with_offset(data, x_left, y + 3 * line_spacing, "cols:");
	draw_dynamic_value(data, x_left, y + 3 * line_spacing, data->grid->cols);
	put_string_with_offset(data, x_left, y + 5 * line_spacing, "max z:");
	draw_dynamic_value(data, x_left, y + 5 * line_spacing, data->max_z);
	put_string_with_offset(data, x_left, y + 6 * line_spacing, "min z:");
	draw_dynamic_value(data, x_left, y + 6 * line_spacing, data->min_z);
	put_string_with_offset(data, x_left, y + 7 * line_spacing, "zoom:");
	draw_dynamic_value(data, x_left, y + 7 * line_spacing, data->scale_zoom);
	put_string_with_offset(data, x_left, y + 8 * line_spacing, "angle x:");
	draw_dynamic_value(data, x_left, y + 8 * line_spacing, data->angle_x);
	put_string_with_offset(data, x_left, y + 9 * line_spacing, "angle y:");
	draw_dynamic_value(data, x_left, y + 9 * line_spacing, data->angle_y);
	put_string_with_offset(data, x_left, y + 10 * line_spacing, "angle z:");
	draw_dynamic_value(data, x_left, y + 10 * line_spacing, data->angle_z);
}

void	draw_information(t_w_data *data)
{
	int	x_left;
	int	y;
	int	line_spacing;

	x_left = data->window_w * 0.05;
	y = data->window_h * 0.1;
	line_spacing = 15;
	draw_static_text(data, x_left, y, line_spacing);
	draw_dynamic_values(data, x_left, y, line_spacing);
	put_string_with_offset(data, x_left, y + 12 * line_spacing, "H - Help");
	put_string_with_offset(data, x_left, y + 13 * line_spacing, "ESC - Exit");
}
