/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:04:17 by joao              #+#    #+#             */
/*   Updated: 2024/10/02 20:50:07 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	project_point(t_w_data *data, int i, int j, float d)
{
	float	projected_x;
	float	projected_y;

	if (data->extra_z != -d)
	{
		projected_x = (data->extra_x / (data->extra_z + d)) * data->scale
			+ data->window_w / 2;
		projected_y = (data->extra_y / (data->extra_z + d)) * data->scale
			+ data->window_h / 2;
	}
	else
	{
		projected_x = data->window_w / 2;
		projected_y = data->window_h / 2;
	}
	data->p[i][j].x = (int)projected_x;
	data->p[i][j].y = (int)projected_y;
}

static void	process_grid_points(t_w_data *data, float d)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			data->extra_x = data->p[i][j].x;
			data->extra_y = data->p[i][j].y;
			data->extra_z = data->p[i][j].z;
			project_point(data, i, j, d);
			j++;
		}
		i++;
	}
}

void	apply_perspective_projection(t_w_data *data)
{
	float	d;

	d = 1.0;
	process_grid_points(data, d);
}

void	transform_p(t_w_data *data)
{
	int		i;
	int		j;
	float	x;
	float	y;
	float	z;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			x = data->p_b[i][j].x;
			y = data->p_b[i][j].y;
			z = data->p_b[i][j].z;
			data->p[i][j].x = (int)(x);
			data->p[i][j].y = (int)(y);
			data->p[i][j].z = (int)z;
			j++;
		}
		i++;
	}
}
