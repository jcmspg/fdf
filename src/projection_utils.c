/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:04:17 by joao              #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void apply_perspective_projection(t_w_data *data)
{
    int i, j;

    // Projection distance (focal length)
    float d = 1000.0f; // Adjust this value based on your desired perspective effect

    float x, y, z;
    float projected_x, projected_y;

    for (i = 0; i < data->grid->rows; i++)
    {
        for (j = 0; j < data->grid->cols; j++)
        {
            // Original coordinates
            x = data->p[i][j].x;
            y = data->p[i][j].y;
            z = data->p[i][j].z;

            // Apply perspective projection
            if (z != -d) // Avoid division by zero
            {
                projected_x = (x / (z + d)) * data->scale + data->window_w / 2;
                projected_y = (y / (z + d)) * data->scale + data->window_h / 2;
            }
            else
            {
                // Handle the special case where z is -d (p at the projection plane)
                projected_x = data->window_w / 2;
                projected_y = data->window_h / 2;
            }

            // Store the projected coordinates
            data->p[i][j].x = (int)projected_x;
            data->p[i][j].y = (int)projected_y;
        }
    }
}

void transform_p(t_w_data *data)
{
	int i;
	int j;

	float x;
	float y;
	float z;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			x = data->p_b[i][j].x;
			y = data->p_b[i][j].y;
			z = data->p_b[i][j].z;

			// Apply the transformation
			data->p[i][j].x = (int)(x);
			data->p[i][j].y = (int)(y);
			data->p[i][j].z = (int)z;

			j++;
		}
		i++;
	}
}

