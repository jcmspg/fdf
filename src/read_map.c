/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:15:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/20 17:07:29 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// get_next_line: reads a line from the file descriptor
// counts the number of lines and columns in the file
static void  count_grid(int fd, t_grid *grid)
{
    char    *line;
    int     num_lines;
    int     num_cols;
    int     i;

    num_lines = 0;
    num_cols = 0;
    i = 0;
    line = get_next_line(fd);

    while (line[i] != '\n' && line[i] != '\0')
    {
        if (ft_isdigit(line[i]))
        {
            num_cols++;
            while (ft_isdigit(line[i]))
                i++;
        }
        else
            i++;
    }
    while (line)
    {
        num_lines++;
        free(line);
        line = get_next_line(fd);
    }

    free(line);

    grid->cols = num_cols;
    grid->rows = num_lines;
}

//read_fdf: reads the file and counts the number of lines and columns
void    read_fdf(const char *file, t_grid *grid)
{
    int     fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error: Could not open file %s\n", file);
        exit(1);
    }
    
    count_grid(fd, grid);
    close(fd);
}


