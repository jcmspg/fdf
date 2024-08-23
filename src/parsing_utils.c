/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:24 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/23 19:32:32 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

char **info_parser(int fd, w_data *data)
{
    char **z_values;
    char *line;
    int i;

    z_values = ft_calloc(data->grid->rows, sizeof(char *));
    if (!z_values)
    {
        fprintf(stderr, "Error: Could not allocate memory for z_values\n");
        exit(1);
    }

    i = 0;
    while (i < data->grid->rows)
    {
        line = get_next_line(fd);
        if (!line)
        {
            fprintf(stderr, "Error: Failed to read line from file\n");
            exit(1);
        }

        z_values[i] = ft_strdup(line); // or copy the content properly
        if (!z_values[i])
        {
            fprintf(stderr, "Error: Failed to allocate memory for z_values[%d]\n", i);
            free(line);
            exit(1);
        }

        free(line);
        i++;
    }
    return z_values;
}

int ft_getcolor(const char *str)
{
    char **color;
    int i;
    int j;

    j = 0;

    color = ft_split(str, ',');
    if (!color)
    {
        fprintf(stderr, "Error: Could not allocate memory for color values\n");
        exit(1);
    }
    i = 0;
    if (color[1])
    {
        if (ft_strncmp(color[1], "0x", 2))
        {
            fprintf(stderr, "Error: Color value is not in hexadecimal format\n");
            free(color);
            exit(1);
        }
        i = ft_atoi_base(color[1] + 2, 16);
    }
    while (color[j])
    {
        free(color[j]);
        j++;
    }
    return (i);
}

void assign_info(w_data *data)
{
    int i;
    int j;
    char **split_line;

    i = 0;
    j = 0;

    while (i < data->grid->rows)
    {
        split_line = ft_split(data->z_values[i], ' ');
        if (!split_line)
        {
            fprintf(stderr, "Error: Could not allocate memory for split line\n");
            exit(1);
        }
        j = 0;
        while (j < data->grid->cols)
        {
            data->points[i][j].z = ft_atoi(split_line[j]);
            data->points[i][j].color = ft_getcolor(split_line[j]);
            j++;
        }
        while (split_line[j])
        {
            free(split_line[j]);
            j++;
        }
        free(split_line);
        i++;
    }
}

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
            printf("Point[%d][%d]: x = %d, y = %d, z = %d, color = %d\n", i, j, data->points[i][j].x, data->points[i][j].y, data->points[i][j].z, data->points[i][j].color);
            j++;
        }
        i++;
    }
}
       
//reads the file and assigns important values to the data struct
void    read_fdf(const char *file, w_data *data)
{
    int     fd;

    //checking if the file is in the correct format
    //and opening the file
    
    if (!format_checker(file))
        exit(1);

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error: Could not open file %s\n", file);
        exit(1);
    }
   
    //counting the number of lines and columns in the file
    count_grid(fd, data);
    printf("Rows: %d\nCols: %d\n", data->grid->rows, data->grid->cols);
    close(fd);

    //reopening the file to read the values
    fd = open(file, O_RDONLY);
    // making the points array
    data->points = make_points(data);
    // getting the Z and color values from the file
    data->z_values = info_parser(fd, data);


    //assigning the Z and color values to the points array
    assign_info(data);

    //printing the points coords and colors
    print_data(data);

    //closing the file
    close(fd);
}

