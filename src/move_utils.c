/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:28:26 by joao              #+#    #+#             */
/*   Updated: 2024/10/02 18:03:48 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to reset the position of the p
void	reset_position(t_w_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->p != NULL)
	{
		while (i < data->grid->rows)
		{
			j = 0;
			while (j < data->grid->cols)
			{
				data->p[i][j].x = data->p_b[i][j].x;
				data->p[i][j].y = data->p_b[i][j].y;
				data->p[i][j].z = data->p_b[i][j].z;
				data->p[i][j].color = data->p_b[i][j].color;
				j++;
			}
			i++;
		}
	}
	data->scale_z = SCALE_FACTOR_Z;
}

void	restore_origin(t_w_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->p != NULL)
	{
		while (i < data->grid->rows)
		{
			j = 0;
			while (j < data->grid->cols)
			{
				data->p_b[i][j].x = data->p_restore[i][j].x;
				data->p_b[i][j].y = data->p_restore[i][j].y;
				data->p_b[i][j].z = data->p_restore[i][j].z;
				data->p_b[i][j].color = data->p_restore[i][j].color;
				data->p[i][j].x = (int)data->p_b[i][j].x;
				data->p[i][j].y = (int)data->p_b[i][j].y;
				data->p[i][j].z = (int)data->p_b[i][j].z;
				data->p[i][j].color = data->p_b[i][j].color;
				j++;
			}
			i++;
		}
	}
	data->scale = 1;
}
