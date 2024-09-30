/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:27:47 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/30 18:29:58 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pcoords_conic(w_data *data)
{
	float	vp_x;
	float	vp_y;

	vp_x = data->window_w / 2;
	vp_y = data->window_h *(2 / 3);
	data->spr = ISO_TILT;
	data->i = 0;
	data->j = 0;
	while (data->i < data->grid->rows)
	{
		while (data->j < data->grid->cols)
		{
			data->scale += (F_L / (F_L + data->i_p[data->i][data->j].y));
			data->p_b[data->i][data->j].x = vp_x
				+ (data->i_p[data->i][data->j].x - vp_x) * data->scale;
			data->p_b[data->i][data->j].y = vp_y + ((data->i * data->spr)
					- data->i_p[data->i][data->j].z) * data->scale;
			data->p[data->i][data->j].x = (int)(data->p_b[data->i][data->j].x);
			data->p[data->i][data->j].y = (int)(data->p_b[data->i][data->j].y);
			data->j++;
		}
		data->j = 0;
		data->i++;
	}
}

void	change_aero(int key, w_data *data)
{
	if (key == W)
		data->spr += 5;
	if (key == S)
		data->spr -= 5;
}

void	change_focal_d(int key, w_data *data)
{
	if (key == A)
		data->scale += 0.5;
	if (key == D)
		data->scale -= 0.5;
}

void	build_conic(w_data *data)
{
	clear_image(data);
	pcoords_conic(data);
	calc_sc_mid(data);
	scale_center(data);
	color_mode(data);
	draw_poly(data);
	make_image(data);
}
