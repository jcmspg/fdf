/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:11 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/28 20:17:47 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_data(w_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            printf("Point[%d][%d]: x = %d, y = %d, z = %d, color = %x\n", i, j, data->points[i][j].x, data->points[i][j].y, data->points[i][j].z, data->points[i][j].color);
            j++;
        }
        i++;
    }
}

bool format_checker (const char *file)
{
    if (!file)
    {
        fprintf(stderr, "Error: No file specified\n");
        return (false);
    }

    // checker to see if file is .fdf format
    if (ft_strncmp(file + ft_strlen(file) - 4, ".fdf", 4))
    {
        fprintf(stderr, "Error: File is not in .fdf format\n");
        return (false);
    }
    return (true);
}

// function to free any number of pointers
void free_pointers(void *ptr, ...)
{
    va_list args;
    void *tmp;

    va_start(args, ptr);
    tmp = ptr;
    while (tmp)
    {
        free(tmp);
        tmp = va_arg(args, void *);
    }
    va_end(args);
}