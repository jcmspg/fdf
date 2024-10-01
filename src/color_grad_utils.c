/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_grad_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:56:04 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 18:06:47 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_positive_color(int z, int max_z)
{
	double	ratio;

	ratio = (double)z / (double)max_z;
	return ((int)(255 * ratio) << 16 | (int)(255 * (1 - ratio)) << 8);
}

int	get_negative_color(int z, int min_z)
{
	double	ratio;

	ratio = (double)(-z) / (double)(-min_z);
	return ((int)(255 * ratio) | (int)(255 * (1 - ratio)) << 8);
}

int	get_zero_color(void)
{
	return (YELLOW);
}

int	calculate_color(int z, int min_z, int max_z)
{
	if (z > 0)
		return (get_positive_color(z, max_z));
	else if (z < 0)
		return (get_negative_color(z, min_z));
	else
		return (get_zero_color());
}

void	colorize_gradient(t_w_data *data)
{
	data->i = 0;
	while (data->i < data->grid->rows)
	{
		data->j = 0;
		while (data->j < data->grid->cols)
		{
			data->p[data->i][data->j].color
				= calculate_color(data->p[data->i][data->j].z,
					data->min_z, data->max_z);
			data->j++;
		}
		data->i++;
	}
}
