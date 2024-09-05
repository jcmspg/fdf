/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:04:17 by joao              #+#    #+#             */
/*   Updated: 2024/09/05 19:07:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void apply_perspective_projection(w_data *data)
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
            x = data->points[i][j].x;
            y = data->points[i][j].y;
            z = data->points[i][j].z;

            // Apply perspective projection
            if (z != -d) // Avoid division by zero
            {
                projected_x = (x / (z + d)) * data->scale + data->window_width / 2;
                projected_y = (y / (z + d)) * data->scale + data->window_height / 2;
            }
            else
            {
                // Handle the special case where z is -d (points at the projection plane)
                projected_x = data->window_width / 2;
                projected_y = data->window_height / 2;
            }

            // Store the projected coordinates
            data->points[i][j].x = (int)projected_x;
            data->points[i][j].y = (int)projected_y;
        }
    }
}

void transform_points(w_data *data)
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
			x = data->points_backup[i][j].x;
			y = data->points_backup[i][j].y;
			z = data->points_backup[i][j].z;

			// Apply the transformation
			data->points[i][j].x = (int)(x);
			data->points[i][j].y = (int)(y);
			data->points[i][j].z = (int)z;

			j++;
		}
		i++;
	}
}

