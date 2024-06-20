/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:08:41 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/20 19:40:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int total_points(t_grid *grid)
{
    int rows;
    int cols;
    int total;

    rows = grid->rows;
    cols = grid->cols;
    total = rows * cols;

    return (total);
}
