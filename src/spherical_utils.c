/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:55:09 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/04 21:03:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void pcoords_spherical(w_data *data)
{
    int i;
	int j;
    float x_spherical;
	float y_spherical;
	float z_spherical;
    float latitude;
	float longitude;
// float x;
// float y;
	float z;

    float radius;
    float radius_with_elevation;
	float maximum_z;

    // Use a constant radius for the globe
    radius = data->radius; 

	maximum_z = data->max_z;

    i = 0;
    j = 0;

    while (i < data->grid->rows)
    {
        while (j < data->grid->cols)
        {
            // Normalize grid indices to latitude and longitude
            latitude = ((float)i / (data->grid->rows - 1)) * PI - (PI / 2); // Latitude: -π/2 to π/2
            longitude = ((float)j / (data->grid->cols - 1)) * 2 * PI - PI;    // Longitude: -π to π

            // Get the elevation or height (z-value)
            
		//	x = data->iso_points[i][j].x;
		//	y = data->iso_points[i][j].y;
			z = data->iso_points[i][j].z;

            // Compute the radius with elevation
            radius_with_elevation = radius + z * (radius / maximum_z / 4);

            // Compute spherical coordinates
            x_spherical = radius_with_elevation * cos(latitude) * cos(longitude);
            y_spherical = radius_with_elevation * cos(latitude) * sin(longitude);
            z_spherical = (radius_with_elevation * sin(latitude));

            // Convert to screen coordinates (center the globe)
            data->points[i][j].x = (int)(x_spherical + data->window_width / 2);
            data->points[i][j].y = (int)(y_spherical + data->window_height / 2);
            data->points[i][j].z = (int)z_spherical;

            // Optionally, store backup
            data->points_backup[i][j].x = x_spherical;
            data->points_backup[i][j].y = y_spherical;
            data->points_backup[i][j].z = z_spherical;

            j++;
        }
        j = 0;
        i++;
    }
}

void project_to_2d(w_data *data) {
	
	int i;
	float center_x = data->window_width / 2;
	float center_y = data->window_height / 2;

	for (i = 0; i < data->grid->rows; i++)
	{
		for (int j = 0; j < data->grid->cols; j++)
		{
			float x = data->points_backup[i][j].x;
			float y = data->points_backup[i][j].y;

			data->points_backup[i][j].x = x + center_x;
			data->points_backup[i][j].y = y + center_y;
			
            // Convert 3D coordinates to 2D
			
			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].y = (int)data->points_backup[i][j].y;
        }
    }
}

void orbit(w_data *data)
{
	int i;
	int j;

	float x;
	float y;
	float z;

	float original_x;
	float original_y;
	float original_z;

	float new_x;
	float new_z;

	float center_y;
	float center_x;

	float cos_angle;
	float sin_angle;

	data->angle_y %= DEGREE_MAX;
	if (data->angle_y < 0)
		data->angle_y += DEGREE_MAX;

	cos_angle = data->lookup->cos_table[data->angle_y];
	sin_angle = data->lookup->sin_table[data->angle_y];

	center_y = data->window_height / 2;
	center_x = data->window_width / 2;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			original_x = data->points_backup[i][j].x;
			original_y = data->points_backup[i][j].y;
			original_z = data->points_backup[i][j].z;

			// Apply rotation around the Y-axis
			x = original_x - center_x;
			y = original_y - center_y;
			z = original_z;

			new_x = (x * cos_angle - z * sin_angle) / SCALE_TRIG;
			new_z = (x * sin_angle + z * cos_angle) / SCALE_TRIG;

			data->points_backup[i][j].x = new_x + center_x;
			data->points_backup[i][j].y = y + center_y;
			data->points_backup[i][j].z = new_z;

			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].y = (int)data->points_backup[i][j].y;
			data->points[i][j].z = (int)data->points_backup[i][j].z;

			j++;
		}
	}
}

void change_tilt(w_data *data)
{
	int i;
	int j;
    float x;
	float y;
	float z;
	
    float y_rot;
	float z_rot;
    float angle_x;

    angle_x = degree_to_radian(data->angle_x);

    float cos_x = cos(angle_x);
    float sin_x = sin(angle_x);

    for (i = 0; i < data->grid->rows; i++) {
        for (j = 0; j < data->grid->cols; j++) {
            x = data->points_backup[i][j].x;
            y = data->points_backup[i][j].y;
			z = data->points_backup[i][j].z;

            // Apply rotation around the X-axis
            y_rot = y * cos_x - z * sin_x;
			z_rot = y * sin_x + z * cos_x;

            // Save rotated point
            data->points_backup[i][j].x = x;
            data->points_backup[i][j].y = y_rot;
            data->points_backup[i][j].z = z_rot;
        }
    }
}

void ro_sphere(int key, w_data *data)
{
	if (key == A || key == D)
	{
		if (key == A)
			data->angle_y -= ANGLE_VALUE;
		if (key == D)
			data->angle_y += ANGLE_VALUE;
		orbit(data);
		project_to_2d(data);
	}
	if (key == Q || key == E)
	{
		if (key == Q)
			data->angle_x -= ANGLE_VALUE;
		if (key == E)
			data->angle_x += ANGLE_VALUE;
		change_tilt(data);
		project_to_2d(data);
	}
update_img(data);
}

void build_sphere(w_data *data)
{
	clear_image(data);
	pcoords_spherical(data);
//	calc_sc_mid(data);
//	scale_center(data);
	color_mode(data);
	draw_poly(data);
	make_image(data);
}
