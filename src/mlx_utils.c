/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:58:44 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 21:07:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*init_mlx(void)
{
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
	{
		perror("Error initializing mlx\n");
		return (NULL);
	}
	return (mlx);
}

// create a new Window
void	create_window(t_w_data *data)
{
	data->win = mlx_new_window(data->mlx, data->window_w,
			data->window_h, data->title);
	if (!data)
	{
		perror("Error creating window\n");
		return ;
	}
}

// Create a new image
void	create_image(t_w_data *data)
{
	data->img.img = mlx_new_image(data->mlx, data->window_w, data->window_h);
	if (!data->img.img)
	{
		perror("Error creating image\n");
		return ;
	}
	data->img.address = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	if (!data->img.address)
	{
		perror("Error getting image address\n");
		return ;
	}
}

void	make_image(t_w_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	my_mlx_pixel_put(t_w_data *data, int x, int y, int color)
{
	char	*distance;

	if (x < 0 || x >= data->window_w || y < 0 || y >= data->window_h)
		return ;
	distance = data->img.address
		+ (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int *)distance = color;
}
