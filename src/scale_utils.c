/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:16:25 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/21 18:31:48 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Functions to scale the map
// 
// determining the maximum grid size
//

//
//
// scaling function to fit the window
void scale_grid(w_data *data)
{
    int i;
    int j;
    int scale_factor_x;
    int scale_factor_y;
    int scale_factor;

    scale_factor_x = data->window_width / data->grid->cols / 2;
    scale_factor_y = data->window_height / data->grid->rows / 2;

    if (scale_factor_x < scale_factor_y)
        scale_factor = scale_factor_x;
    else
        scale_factor = scale_factor_y;

    i = 0;
    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            data->points[i][j].x *= scale_factor;
            data->points[i][j].y *= scale_factor;
            data->points[i][j].z *= scale_factor;
            j++;
        }
        i++;
    }
    data->scale = scale_factor;    
}
