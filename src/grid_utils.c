/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:08:41 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/21 20:20:40 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
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

void point_maker(int fd, t_grid *grid)
{
    char *line;
    point **p;
    int i;
    int z;
    int ip;

    line = get_next_line(fd);
    i = 0;
    z = 0;

    while (line)
    {
        if (line[i] != '\n' && line[i] != '\0')
        {
            if (ft_isdigit(line[i]) || line[i] == '-')
            {
                z = ft_atoi(line[i]);
                p[ip++] = create_point(0, 0, z);
                z = 0;
                while (ft_isdigit(line[i]) || line[i] == '-')
                    i++;
            }
            else
                i++;
        }
        else
        {
            i = 0;
            free(line);
            line = get_next_line(fd);
        }
    }
}
*/
