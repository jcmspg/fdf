/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:11:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/24 17:36:28 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Data functions
void free_data(w_data *win)
{
    mlx_destroy_image(win->mlx, win->img.img);
    mlx_destroy_window(win->mlx, win->win);
    mlx_destroy_display(win->mlx);
    free(win->mlx);
}

int close_window(w_data *win)
{
    free_data(win);
    exit(0);
}

// keyboard interactions function
int key_handle(int key, w_data *win)
{
    if (key == ESC)
        close_window(win);
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
void create_window(w_data *window)
{
    window->win = mlx_new_window(window->mlx, window->window_width, window->window_height, window->title);
    if (!window)
    {
        fprintf(stderr, "Error creating window\n");
        return;
    }
}


//Create a new image
void    create_image(w_data *window)
{
    window->img.img = mlx_new_image(window->mlx, window->window_width, window->window_height);
    if (!window->img.img)
    {
        fprintf(stderr, "Error creating image\n");
        return; 
    }
    window->img.address = mlx_get_data_addr(window->img.img, &window->img.bits_per_pixel, &window->img.line_length, &window->img.endian);
    if (!window->img.address)
    {
        fprintf(stderr, "Error getting image address\n");
        return;
    }
}
