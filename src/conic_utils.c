/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:27:47 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/04 19:31:44 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void pcoords_conic(w_data *data)
{
	int i;
	int j;

	float x_conic;
	float y_conic;

	float x;
	float y;
	float z;

	float vp_x;
	float vp_y;

	vp_x = data->window_width / 2;
	vp_y = data->window_height * (2/3);

	data->spread = ISO_TILT;

	i = 0;
	j = 0;

	while (i < data->grid->rows)
	{
		while (j < data->grid->cols)
		{
			x = data->iso_points[i][j].x;
			y = data->iso_points[i][j].y;
			z = data->iso_points[i][j].z;

			data->scale += (FOCAL_LENGTH / (FOCAL_LENGTH + y));

			x_conic = vp_x + (x - vp_x) * data->scale;
			y_conic = vp_y + ((i * data->spread)- z) * data->scale;

			data->points[i][j].x = (int) x_conic;
			data->points[i][j].y = (int) y_conic;

			data->points_backup[i][j].x = x_conic;
			data->points_backup[i][j].y = y_conic;

			j++;
		}
		j = 0;
		i++;
	}
}

void change_aero(int key, w_data *data)
{
	if (key == W)
		data->spread += 5;
	if (key == S)
		data->spread -= 5;
}

void change_focal_d(int key, w_data *data)
{
	if (key == A)
		data->scale += 0.5;
	if (key == D)
		data->scale -= 0.5;
}



	void build_conic(w_data *data)
{
	clear_image(data);
	pcoords_conic(data);
	calc_sc_mid(data);
	scale_center(data);
	color_mode(data);
	draw_poly(data);
	make_image(data);
}

