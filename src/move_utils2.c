/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:00:05 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:31:31 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_movement(int keycode, t_w_data *data, int *mov_x, int *mov_y)
{
	*mov_x = 0;
	*mov_y = 0;
	if (keycode == W)
		*mov_y = (data->window_h / MOVE_FACTOR);
	if (keycode == A)
		*mov_x = (data->window_w / MOVE_FACTOR);
	if (keycode == S)
		*mov_y = -(data->window_h / MOVE_FACTOR);
	if (keycode == D)
		*mov_x = -(data->window_w / MOVE_FACTOR);
}

void	apply_movement(t_w_data *data, int movement_x, int movement_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			data->p[i][j].x += movement_x;
			data->p[i][j].y += movement_y;
			data->p_b[i][j].x += movement_x;
			data->p_b[i][j].y += movement_y;
			j++;
		}
		i++;
	}
}

void	move(int keycode, t_w_data *data)
{
	int	movement_x;
	int	movement_y;

	calculate_movement(keycode, data, &movement_x, &movement_y);
	apply_movement(data, movement_x, movement_y);
}
