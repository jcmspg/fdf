/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:31:37 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/30 18:31:20 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_grid(w_data *data)
{
	data->grid->rows = 0;
	data->grid->cols = 0;
}

void	init_data_w(w_data *data)
{
	data->window_h = WINDOW_H;
	data->window_w = WINDOW_W;
	data->scale = 1.0;
	data->scale_zoom = 1.0;
	data->mode = 0;
	init_grid(data);
	init_angle(data);
}
