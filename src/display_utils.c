/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:11:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/21 20:12:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Data functions
void free_data(w_data *data)
{
    mlx_destroy_image(data->mlx, data->img.img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
}

int close_window(w_data *data)
{
    int i;

    i = 0;

   while (data->map[i])
    {
        free(data->map[i]);
        i++;
    }
   i = 0;
   while (data->points[i])
    {
        free(data->points[i]);
        i++;
    }
    free(data->points);
    free(data->grid);
    free(data->map);
    free_data(data);
    exit(0);
}

// keyboard interactions function
int key_handle(int key, w_data *data)
{
    if (key == ESC)
        close_window(data);
    return 0;
}

//Image functions

// mlx initialization and checks
void *init_mlx(void)
{
    void *mlx;

    mlx = mlx_init();
    if (!mlx)
    {
        fprintf(stderr, "Error initializing mlx\n");
        return NULL;
    }
    return mlx;
}

// create a new Window
void create_window(w_data *data)
{
    data->win = mlx_new_window(data->mlx, data->window_width, data->window_height, data->title);
    if (!data)
    {
        fprintf(stderr, "Error creating window\n");
        return;
    }
}


//Create a new image
void    create_image(w_data *data)
{
    data->img.img = mlx_new_image(data->mlx, data->window_width, data->window_height);
    if (!data->img.img)
    {
        fprintf(stderr, "Error creating image\n");
        return; 
    }
    data->img.address = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    if (!data->img.address)
    {
        fprintf(stderr, "Error getting image address\n");
        return;
    }
}
