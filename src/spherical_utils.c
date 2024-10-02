/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:55:09 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:30:25 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	calculate_latitude(int i, int rows)
{
	return (((float)i / (rows - 1)) * PI - (PI / 2));
}

float	calculate_longitude(int j, int cols)
{
	return (((float)j / (cols - 1)) * 2 * PI - PI);
}

float	compute_radius_with_elevation(float z, float radius, float max_z)
{
	return (radius + z * (radius / max_z / 10));
}

void	update_coordinates(t_w_data *data, int i, int j, float radius_with_elev)
{
	float	latitude;
	float	longitude;
	float	x_spherical;
	float	y_spherical;
	float	z_spherical;

	latitude = calculate_latitude(i, data->grid->rows);
	longitude = calculate_longitude(j, data->grid->cols);
	x_spherical = radius_with_elev * cos(latitude) * cos(longitude);
	y_spherical = radius_with_elev * cos(latitude) * sin(longitude);
	z_spherical = radius_with_elev * sin(latitude);
	data->p_b[i][j].x = x_spherical + data->window_w / 2.0f;
	data->p_b[i][j].y = y_spherical + data->window_h / 2.0f;
	data->p_b[i][j].z = z_spherical;
	data->p[i][j].x = (int)(data->p_b[i][j].x);
	data->p[i][j].y = (int)(data->p_b[i][j].y);
	data->p[i][j].z = (int)(data->p_b[i][j].z);
}

void	pcoords_spherical(t_w_data *data)
{
	int		i;
	int		j;
	float	radius_with_elev;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			radius_with_elev = compute_radius_with_elevation(
					data->i_p[i][j].z, data->radius, data->max_z);
			update_coordinates(data, i, j, radius_with_elev);
			j++;
		}
		i++;
	}
	data->scale = 1;
}
