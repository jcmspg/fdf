/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:33:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_horizontal_sph(t_w_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols - 1)
		{
			if (data->p[i][j].z >= 0 && data->p[i][j + 1].z >= 0)
				draw_line(data, &data->p[i][j], &data->p[i][j + 1]);
			j++;
		}
		i++;
	}
}

void	draw_vertical_sph(t_w_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->cols)
	{
		j = 0;
		while (j < data->grid->rows - 1)
		{
			if (data->p[j][i].z >= 0 && data->p[j + 1][i].z >= 0)
				draw_line(data, &data->p[j][i], &data->p[j + 1][i]);
			j++;
		}
		i++;
	}
}

void	draw_poly_spherical(t_w_data *data)
{
	draw_horizontal_sph(data);
	draw_vertical_sph(data);
}
