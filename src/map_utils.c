/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:15:46 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/22 20:02:09 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// get_next_line: reads a line from the file descriptor
// counts the number of lines and columns in the file

/*
static int len_line(char **c){
    int i = 0;
    while (c[i])
        i++;
    return (i);
}

*/


static void  count_grid(int fd, w_data *data)
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

    data->grid->cols = num_cols;
    data->grid->rows = num_lines;
}

//read_fdf: reads the file and counts the number of lines and columns
void    read_fdf(const char *file, w_data *data)
{
    int     fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error: Could not open file %s\n", file);
        exit(1);
    }
    
    count_grid(fd, data);
    close(fd);
}

// map_alloc: allocates memory for the map and creates a 2D array for the Z values of points
int **map_alloc(const char *file, w_data *data)
{
    int     **map;
    int     fd;
    char    *line;
    char    **split_line;
    int     i;
    int     j;
 


    map = (int **)ft_calloc(sizeof(int*), data->grid->rows * data->grid->cols);
    if (!map)
    {
        fprintf(stderr, "Error: Could not allocate memory for map\n");
        exit(1);
    }

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error: Could not open file %s\n", file);
        exit(1);
    }

    i = 0;
    while (i < data->grid->rows)
    {
        line = get_next_line(fd);
        split_line = ft_split(line,' ' );
        map[i] = (int *)ft_calloc(sizeof(int) , data->grid->cols);
        if (!map[i])
        {
            fprintf(stderr, "Error: Could not allocate memory for map\n");
            exit(1);
        }
        j = 0;
        while (j < data->grid->cols)
        {
            map[i][j] = ft_atoi(split_line[j]);
            j++;
        }
        free(line);
        while (j >= 0)
        {
            free(split_line[j]);
            j--;
        }
        free(split_line);
        i++;
    }
    close(fd);
    return (map);
}





// populate_grid: fills the grid with the points
// points is a 2D array of characters
// each character is a point in the grid
// the character is the Z value of the point


//center_grid: centers the grid in the window
//
//
void center_grid (w_data *data)
{
    int i;
    int j;
    int lines;
    int cols;

    lines = data->grid->rows;
    cols = data->grid->cols;
    
         
    i = 0;
    while (i < lines)
    {
        j = 0;
        while (j < cols)
        {
            data->points[i][j].x += data->grid->half_x;
            data->points[i][j].y += data->grid->half_y;
            j++;
        }
        i++;
    }
}


// make array of points to then assign coordinates to them
t_point **make_points(w_data *data)
{
    int lines;
    int cols;
    int i;
    int j;
    t_point **points;

    lines = data->grid->rows;
    cols = data->grid->cols;
    
    points = (t_point **)ft_calloc(sizeof(t_point *) , (cols * lines));
    if (!points)
    {
        fprintf(stderr, "Error: Could not allocate memory for points\n");
        exit(1);
    }
    i = 0;
    while (i < lines)
    {
        points[i] = (t_point *)ft_calloc(sizeof(t_point) , cols);
        if (!points[i])
        {
            fprintf(stderr, "Error: Could not allocate memory for points\n");
            while (i >= 0)
            {
                free(points[i]);
                i--;
            }
            free(points);
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < lines)
    {
        j = 0;
        while (j < cols)
        {
            points[i][j].x = j * (pointcalc(data));
            points[i][j].y = i * (pointcalc(data));
            points[i][j].z = 10;
            j++;

        }
        i++;
    }


    data->grid->half_x = (data->window_width / 2) - (points[0][cols - 1].x / 2);
    data->grid->half_y = (data->window_height / 2) - (points[lines - 1][0].y / 2);

    return (points);    
}
