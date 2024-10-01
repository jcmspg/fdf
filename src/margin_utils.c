/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   margin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:40:38 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 21:06:08 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_boundaries(t_w_data *data)
{
	data->grid->min_x = data->p[0][0].x;
	data->grid->max_x = data->p[0][0].y;
	data->grid->min_y = data->p[0][0].x;
	data->grid->max_y = data->p[0][0].y;
}

void	update_boundaries(t_w_data *data)
{
	if (data->p[data->i][data->j].x < data->grid->min_x)
		data->grid->min_x = data->p[data->i][data->j].x;
	if (data->p[data->i][data->j].y < data->grid->min_y)
		data->grid->min_y = data->p[data->i][data->j].y;
	if (data->p[data->i][data->j].x > data->grid->max_x)
		data->grid->max_x = data->p[data->i][data->j].x;
	if (data->p[data->i][data->j].y > data->grid->max_y)
		data->grid->max_y = data->p[data->i][data->j].y;
}

void	calc_boundaries(t_w_data *data)
{
	initialize_boundaries(data);
	data->i = 0;
	while (data->i < data->grid->rows)
	{
		data->j = 0;
		while (data->j < data->grid->cols)
		{
			update_boundaries(data);
			data->j++;
		}
		data->i++;
	}
}
