/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_grayscale_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:01:01 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 18:09:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	assign_base_gray_color(int z, int max_z, int min_z)
{
	if (z == 0)
		return (MEDIUM_GRAY);
	else if (z == max_z)
		return (LIGHT_GRAY);
	else if (z == min_z)
		return (DARK_GRAY);
	return (-1);
}

int	calculate_gray_value(int z, int min_z, int range)
{
	double	ratio;

	ratio = ((double)z - min_z) / range;
	return ((int)(64 + ratio * (192 - 64)));
}

int	calculate_and_set_grayscale(t_w_data *data)
{
	int	z;
	int	range;
	int	color;
	int	gray;

	z = data->p[data->i][data->j].z;
	range = data->max_z - data->min_z;
	if (range == 0)
		range = 1;
	color = assign_base_gray_color(z, data->max_z, data->min_z);
	if (color == -1)
	{
		gray = calculate_gray_value(z, data->min_z, range);
		color = (gray << 16) + (gray << 8) + gray;
	}
	return (color);
}

void	colorize_grayscale(t_w_data *data)
{
	data->i = 0;
	while (data->i < data->grid->rows)
	{
		data->j = 0;
		while (data->j < data->grid->cols)
		{
			data->p[data->i][data->j].color = calculate_and_set_grayscale(data);
			data->j++;
		}
		data->i++;
	}
}
