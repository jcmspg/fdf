/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:31:37 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/13 19:21:12 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_data_w(w_data *data)
{
	//initialize window sizes
	data->window_height = WINDOW_H;
	data->window_width = WINDOW_W;

	data->scale = 1.0;

	

	init_angle(data);
	
}




