/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:55:09 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void pcoords_spherical(t_w_data *data)
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

		//	x = data->i_p[i][j].x;
		//	y = data->i_p[i][j].y;
			z = data->i_p[i][j].z;

            // Compute the radius with elevation
            radius_with_elevation = radius + z * (radius / maximum_z / 10);

            // Compute spherical coordinates
            x_spherical = radius_with_elevation * cos(latitude) * cos(longitude);
            y_spherical = radius_with_elevation * cos(latitude) * sin(longitude);
            z_spherical = (radius_with_elevation * sin(latitude));

            // Optionally, store backup
            data->p_b[i][j].x = x_spherical + data->window_w / 2.0f;
            data->p_b[i][j].y = y_spherical + data->window_h / 2.0f;
            data->p_b[i][j].z = z_spherical;

		    // Convert to screen coordinates (center the globe)
            data->p[i][j].x = (int)(data->p_b[i][j].x);
            data->p[i][j].y = (int)(data->p_b[i][j].y);
            data->p[i][j].z = (int)(data->p_b[i][j].z);

            j++;
        }
        j = 0;
        i++;
    }
	data->scale = 1;
}



void orbit(t_w_data *data)
{
	int i;
	int j;

	float cos_angle;
	float sin_angle;
	float angle_x;

	float x;
	float y;
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
			x = data->p_b[i][j].x - data->window_w / 2.0f;
			y = data->p_b[i][j].y - data->window_h / 2.0f;
			z = data->p_b[i][j].z;


			x_new = x * cos_angle + z * sin_angle;
			z_new = -x * sin_angle + z * cos_angle;

			data->p_b[i][j].x = x_new + data->window_w / 2.0f;
			data->p_b[i][j].y = y + data->window_h / 2.0f;
			data->p_b[i][j].z = z_new;

			/* data->p[i][j].x = (int)data->p_b[i][j].x;
			data->p[i][j].y = (int)data->p_b[i][j].y;
			data->p[i][j].z = (int)data->p_b[i][j].z;
 */
			j++;
		}
		i++;
	}
	apply_zoom(data);
}

void change_tilt(t_w_data *data)
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
			x = data->p_b[i][j].x - data->window_w / 2.0f;
			y = data->p_b[i][j].y - data->window_h / 2.0f;
			z = data->p_b[i][j].z;

			y_new = y * cos_angle - z * sin_angle;
			z_new = y * sin_angle + z * cos_angle;


			data->p_b[i][j].x = x + data->window_w / 2.0f;
			data->p_b[i][j].y = y_new + data->window_h / 2.0f;
			data->p_b[i][j].z = z_new;

			/* data->p[i][j].x = (int)data->p_b[i][j].x;
			data->p[i][j].y = (int)data->p_b[i][j].y;
			data->p[i][j].z = (int)data->p_b[i][j].z;
 */
			j++;
		}
		i++;
	}
	apply_zoom(data);
}

void ro_sphere(int key, t_w_data *data)
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

void build_sphere(t_w_data *data)
{
	clear_image(data);
	pcoords_spherical(data);
//	calc_sc_mid(data);
//	scale_center(data);
	color_mode(data);
	draw_poly(data);
	make_image(data);
}
