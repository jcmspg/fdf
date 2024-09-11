/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:31:37 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/11 19:41:52 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_data_w(w_data *data)
{
	//initialize window sizes
	data->window_height = WINDOW_H;
	data->window_width = WINDOW_W;

	data->scale = 1.0;
	
	data->modes[0] = (t_mode) {"Iso", rotate, pan, zoom_in_out, NULL};
	data->modes[1] = (t_mode) {"Spherical", NULL, pan, zoom_in_out, ro_sphere};
	data->modes[2] = (t_mode) {"Conic", NULL, pan, zoom_in_out, NULL};

	data->current_mode = &data->modes[0];

	init_angle(data);
	
}




