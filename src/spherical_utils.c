/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:55:09 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/13 19:01:54 by joamiran         ###   ########.fr       */
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
 //	float x;
 //	float y;
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
            radius_with_elevation = radius + z * (radius / maximum_z / 50);

            // Compute spherical coordinates
            x_spherical = radius_with_elevation * cos(latitude) * cos(longitude);
            y_spherical = radius_with_elevation * cos(latitude) * sin(longitude);
            z_spherical = (radius_with_elevation * sin(latitude));

            // Optionally, store backup
            data->points_backup[i][j].x = x_spherical + data->window_width / 2;
            data->points_backup[i][j].y = y_spherical + data->window_height / 2;
            data->points_backup[i][j].z = z_spherical;
         
		    // Convert to screen coordinates (center the globe)
            data->points[i][j].x = (int)(data->points_backup[i][j].x);
            data->points[i][j].y = (int)(data->points_backup[i][j].y);
            data->points[i][j].z = (int)(data->points_backup[i][j].z);

            j++;
        }
        j = 0;
        i++;
    }
}

void orbit(w_data *data)
{
	int i;
	int j;

	float cos_angle;
	float sin_angle;
	float angle_x;

	float x;
//	float y;
	float z;

	float x_new;
	float z_new;

	angle_x = degree_to_radian(data->angle);
	cos_angle = cos(angle_x);
	sin_angle = sin(angle_x);

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			x = data->points_backup[i][j].x - data->window_width / 2;
		//	y = data->points_backup[i][j].y - data->window_height / 2;
			z = data->points_backup[i][j].z;

			x_new = x * cos_angle + z * sin_angle;
			z_new = -x * sin_angle + z * cos_angle;

			data->points_backup[i][j].x = x_new + data->window_width / 2;
			data->points_backup[i][j].z = z_new;

			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].z = (int)data->points_backup[i][j].z;

			j++;
		}
		i++;
	}
}

void change_tilt(w_data *data)
{
	int i;
	int j;

	float cos_angle;
	float sin_angle;
	float angle_y;

	float x;
	float y;
	float z;

	float y_new;
	float z_new;
//	float x_new;

	angle_y = degree_to_radian(data->angle);
	cos_angle = cos(angle_y);
	sin_angle = sin(angle_y);

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			x = data->points_backup[i][j].x - data->window_width / 2;
			y = data->points_backup[i][j].y - data->window_height / 2;
			z = data->points_backup[i][j].z;

			y_new = y * cos_angle - z * sin_angle;
			z_new = y * sin_angle + z * cos_angle;
		//	x_new = x;

			data->points_backup[i][j].x = x + data->window_width / 2;
			data->points_backup[i][j].y = y_new + data->window_height / 2;
			data->points_backup[i][j].z = z_new;

			data->points[i][j].x = (int)data->points_backup[i][j].x;
			data->points[i][j].y = (int)data->points_backup[i][j].y;
			data->points[i][j].z = (int)data->points_backup[i][j].z;

			j++;
		}
		i++;
	}
}

void ro_sphere(int key, w_data *data)
{
	if (key == A || key == D)
	{
		if (key == A)
		{
			if (data->angle_x >= 360)
				data->angle_x = 0;
			if (data->angle_x < 0)
				data->angle_x = 360;
			data->angle = -ANGLE_VALUE;
			data->angle_x -= ANGLE_VALUE;
		}
		if (key == D)
		{
			if (data->angle_x >= 360)
				data->angle_x = 0;
			if (data->angle_x < 0)
				data->angle_x = 360;
			data->angle = ANGLE_VALUE;
			data->angle_x += ANGLE_VALUE;
		}
		orbit(data);
	}
	if (key == Q || key == E)
	{
		if (key == Q)
		{
			if (data->angle_y >= 360)
				data->angle_y = 0;
			if (data->angle_y < 0)
				data->angle_y = 360;
			data->angle = -ANGLE_VALUE;
			data->angle_y -= ANGLE_VALUE;
		}
		if (key == E)
		{
			if (data->angle_y >= 360)
				data->angle_y = 0;
			if (data->angle_y < 0)
				data->angle_y = 360;
			data->angle = ANGLE_VALUE;
			data->angle_y += ANGLE_VALUE;
		}
		change_tilt(data);
	}
	update_img(data);
	draw_gui(data);
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
