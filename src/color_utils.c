/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:22:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 18:10:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// color the points based on their height
int	height_to_color(int height, int min_height, int max_height)
{
	float	percentage;
	int		color;

	percentage = (float)(height - min_height) / (max_height - min_height);
	color = (int)(percentage * 255);
	return (color);
}

// cycle the points color
void	cycle_color_mode(int key, t_w_data *data)
{
	if (key == C)
	{
		data->color_mode++;
		if (data->color_mode > 2)
			data->color_mode = 0;
	}
}

void	colorize(t_w_data *data)
{
	data->i = 0;
	data->j = 0;
	while (data->i < data->grid->rows)
	{
		while (data->j < data->grid->cols)
		{
			if (!data->p[data->i][data->j].color)
				data->p[data->i][data->j].color = STD_COLOR;
			data->j++;
		}
		data->j = 0;
		data->i++;
	}
}

void	assign_color(t_w_data *data, int *color)
{
	if (data->p[data->i][data->j].z == 0)
		*color = STD_COLOR;
	else if (data->p[data->i][data->j].z == data->max_z)
		*color = MAX_COLOR;
	else if (data->p[data->i][data->j].z == data->min_z)
		*color = MIN_COLOR;
}
