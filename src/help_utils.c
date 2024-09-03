/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 02:50:42 by joao              #+#    #+#             */
/*   Updated: 2024/09/03 03:28:05 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void show_help (w_data *data)
{
    // clear the image
    
    clear_image(data);
    make_image(data);
    
    // display the help
   
    // show a brief help message and description of the program in the middle of the screen
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 - 50, WHITE, "Welcome to FDF");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2, WHITE, "Use the following keys to navigate:");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 20, WHITE, "WASD - Move");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 80, WHITE, "WS - Rotate X");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 40, WHITE, "QE - Rotate Y");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 60, WHITE, "AD - Rotate Z");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 100, WHITE, "C - Change color mode");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 120, WHITE, "P - Pan");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 140, WHITE, "Z - Zoom");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 160, WHITE, "T - Height (BETA WIP)");
    // f to reset
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 180, WHITE, "F - Reset");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 200, WHITE, "H - Help");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 220, WHITE, "ESC - Exit");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 240, WHITE, "Change mode to exit help");

    // display the author's name
    int author_x = data->window_width - 100; // Right aligned
    int author_y = data->window_height - 20; // Bottom aligned
    mlx_string_put(data->mlx, data->win, author_x, author_y, WHITE, "joamiran");
    

}

//function to show an intro scree with brief description of the program

void intro_screen(w_data *data)
{
    // clear the image
    clear_image(data);
    make_image(data);

    // display the intro screen
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 - 50, WHITE, "Welcome to FDF");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2, WHITE, "Press H for help");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 20, WHITE, "Press ESC to exit");
    mlx_string_put(data->mlx, data->win, data->window_width / 2 - 100, data->window_height / 2 + 40, WHITE, "Press SPACE to continue");

    // display the author's name
    int author_x = data->window_width - 100; // Right aligned
    int author_y = data->window_height - 20; // Bottom aligned
    mlx_string_put(data->mlx, data->win, author_x, author_y, WHITE, "joamiran");
}

    