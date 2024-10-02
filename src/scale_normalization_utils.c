/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_normalization_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:55:12 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 21:57:50 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	normalize_z(float z, t_w_data *data)
{
	float	z2;
	float	normalization_factor;

	normalization_factor = 20 / logf(data->max_z + 1.0);
	if (z >= 0)
		z2 = logf(z + 1.0f) * normalization_factor;
	else
		z2 = -logf(-z + 1.0f) * normalization_factor;
	return (z2);
}

void	normalize_z_log(t_w_data *data)
{
	int		max_z;
	float	z;
	float	z2;
	float	normalization_factor;
	float	epsilon;

	epsilon = 0.0001;
	max_z = data->max_z;
	normalization_factor = log(max_z + 1) / log(max_z + 1 + epsilon);
	data->i = 0;
	while (data->i < data->grid->rows)
	{
		data->j = 0;
		while (data->j < data->grid->cols)
		{
			z = data->p_b[data->i][data->j].z;
			if (z < 0)
				z2 = log(z + 1) * normalization_factor * -1;
			else
				z2 = log(z + 1) * normalization_factor * 1;
			data->p_b[data->i][data->j].z = z2;
			data->j++;
		}
		data->i++;
	}
}
