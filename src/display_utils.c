/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:11:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 18:16:22 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Image functions

// draw the updated image
void	update_img(t_w_data *data)
{
	clear_image(data);
	draw_poly(data);
	make_image(data);
}

// clear the image
void	clear_image(t_w_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->window_h)
	{
		x = 0;
		while (x < data->window_w)
		{
			my_mlx_pixel_put(data, x, y, BACKGROUND);
			x++;
		}
		y++;
	}
}

int	close_window(t_w_data *data)
{
	free_data(data);
	exit(0);
}

void	build_model(t_w_data *data)
{
	pcoords_iso(data);
	set_origin(data);
	color_mode(data);
	draw_poly(data);
}
