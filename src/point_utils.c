/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:31:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/07 16:53:48 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	pointcalc(t_w_data *data)
{
	int	height;
	int	width;
	int	distance;

	height = ((data->window_h - (data->window_h / 10)) / data->grid->rows);
	width = ((data->window_w - (data->window_w / 10)) / data->grid->cols);
	if (height < width)
		distance = (height);
	else
		distance = (width);
	return (distance);
}

t_point	*center_point(t_w_data *data)
{
	t_point	*center;

	center = (t_point *)malloc(sizeof(t_point));
	if (!center)
		return (NULL);
	center->x = data->window_w / 2;
	center->y = data->window_h / 2;
	return (center);
}

void	pcoords_iso(t_w_data *data)
{
	float	angle;
	float	x;
	float	y;
	int		i;
	int		j;

	angle = degree_to_radian(30);
	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			if (data->max_z != 0 || data->min_z != 0)
				data->p[i][j].z = (int)normalize_z(data->p_b[i][j].z, data);
			x = data->p[i][j].x;
			y = data->p[i][j].y;
			data->p[i][j].x = (int)(x - y)*cos(angle);
			data->p[i][j].y = (int)(x + y)*sin(angle) - data->p[i][j].z;
			j++;
		}
		i++;
	}
}

void	change_backup(t_w_data *data)
{
	int	lines;
	int	cols;
	int	i;
	int	j;

	lines = data->grid->rows;
	cols = data->grid->cols;
	i = 0;
	while (i < lines)
	{
		j = 0;
		while (j < cols)
		{
			data->p_b[i][j].x = data->p[i][j].x;
			data->p_b[i][j].z = data->p[i][j].z;
			data->p_b[i][j].color = data->p[i][j].color;
			data->p_b[i][j].y = data->p[i][j].y;
			j++;
		}
		i++;
	}
}
