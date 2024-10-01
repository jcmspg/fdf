/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:15:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 18:44:13 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_grid(t_w_data *data)
{
	int	i;
	int	j;
	int	lines;
	int	cols;

	lines = data->grid->rows;
	cols = data->grid->cols;
	i = 0;
	while (i < lines)
	{
		j = 0;
		while (j < cols)
		{
			data->p[i][j].x += data->grid->half_x;
			data->p[i][j].y += data->grid->half_y;
			j++;
		}
		i++;
	}
}

// calc_sc_mid: calculates the middle of the screen and the scale
void	calc_sc_mid(t_w_data *data)
{
	int	vp_width;
	int	vp_height;

	calc_boundaries(data);
	data->grid->width = data->grid->max_x - data->grid->min_x;
	data->grid->height = data->grid->max_y - data->grid->min_y;
	vp_width = data->window_w - (data->window_w / 10);
	vp_height = data->window_h - (data->window_h / 10);
	if (data->grid->width > data->grid->height)
		data->scale = (float)vp_width / data->grid->width;
	else
		data->scale = (float)vp_height / data->grid->height;
	data->mid_x = (data->grid->max_x + data->grid->min_x) / 2;
	data->mid_y = (data->grid->max_y + data->grid->min_y) / 2;
	data->grid->half_x = data->window_w / 2;
	data->grid->half_y = data->window_h / 2;
}

void	scale_center(t_w_data *data)
{
	int		i;
	int		j;
	float	scale;

	scale = data->scale;
	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			data->p[i][j].x = (data->p[i][j].x - data->mid_x)
				* scale + data->grid->half_x;
			data->p[i][j].y = (data->p[i][j].y - data->mid_y)
				* scale + data->grid->half_y;
			data->p[i][j].z = data->p[i][j].z;
			j++;
		}
		i++;
	}
}

void	backup_data(t_w_data *data)
{
	data->p_b = backup_p(data);
	data->p_restore = backup_p(data);
}

void	set_origin(t_w_data *data)
{
	calc_sc_mid(data);
	scale_center(data);
	change_backup(data);
}
