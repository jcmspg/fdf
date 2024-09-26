/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:31:37 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/26 19:24:02 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_grid(w_data *data)
{
	data->grid->rows = 0;
	data->grid->cols = 0;
}



void init_data_w(w_data *data)
{
	//initialize window sizes
	data->window_height = WINDOW_H;
	data->window_width = WINDOW_W;

	data->scale = 1.0;
	data->scale_zoom = 1.0;
	
	data->mode = 0;

	init_grid(data);

	init_angle(data);
	
}




