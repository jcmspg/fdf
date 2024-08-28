/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:24 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/29 00:13:35 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void count_grid(int fd, w_data *data)
{
    char *line;
    char **tmp;
    int num_lines;
    int num_cols;

    num_lines = 0;
    num_cols = -1;
    line = get_next_line(fd);

    if (!line)
    {
        fprintf(stderr, "Error: Failed to read line from file\n");
        exit(1);
    }

    while (line != NULL)
    {
        if (num_cols == -1)
        {
            tmp = ft_split(line, ' ');
            if (!tmp)
            {
                fprintf(stderr, "Error: Could not allocate memory for tmp\n");
                exit(1);
            }
            num_cols = 0;
            while (tmp[num_cols])
            {
                free(tmp[num_cols]);
                num_cols++;
            }
            free(tmp);
        }
        free(line);
        num_lines++;
        line = get_next_line(fd);
    }
    data->grid->cols = num_cols;
    data->grid->rows = num_lines;
}

/*
static int count_columns(const char *line)
{
    int i;
    int count;

    i = 0;0123456789ABCDEF
    count = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (ft_isdigit(line[i]) || line[i] == '-')
        {
            count++;
            while (ft_isdigit(line[i]) || line[i] == '-')
                i++;
            // if theres a comma, we skip the color code
            if (line[i] == ',')
            {
                i++;
                while (ft_isalnum(line[i]))
                    i++;
            }
        }
        else
            i++;0123456789ABCDEF
    }
    return count;
}
*/

// check if theres any color info in the file. If there is, w_data->has_color =1
// if not, w_data->has_color = 0

void check_color(const char *line, w_data *data)
{
    while (*line)
    {
        if (*line == ',')
        {
            data->has_color = true;
            return;
        }
        line++;
    }
}

char **info_parser(int fd, w_data *data)
{
    char **z_values;
    char *line;
    int i;
    //   int expected_cols;
    //   int line_cols;

    z_values = ft_calloc(data->grid->rows, sizeof(char *));
    if (!z_values)
    {
        fprintf(stderr, "Error: Could not allocate memory for z_values\n");
        exit(1);
    }

    //   expected_cols = data->grid->cols;

    i = 0;
    while (i < data->grid->rows)
    {
        line = get_next_line(fd);
        if (!line)
        {
            fprintf(stderr, "Error: Failed to read line from file\n");
            exit(1);
        }

        //     line_cols = count_columns(line);
        /*      if (line_cols != expected_cols)
              {
                  fprintf(stderr, "Error: Line %d has %d columns, expected %d\n", i, line_cols, expected_cols);
                  free(line);
                  while (i > 0)
                  {
                      free(z_values[i]);
                      i--;
                  }
                  exit(1);
              }
      */

        // check if the line has color info
        check_color(line, data);

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
    printf("has color: %i \n", data->has_color);
    return z_values;
}

/*
int ft_getcolor(const char *str)
{
    char **color;
    int i;
    int j;
    int k;

    j = 0;

    color = ft_split(str, ',');
    if (!color)
    {
        fprintf(stderr, "Error: Could not allocate memory for color values\n");
        exit(1);
    }


    i = 0; // if the color is not in the correct format, we set it to 0
           // if it is, we convert it to an int
    if (color[1] && color[1][0] == '0' && (color[1][1] == 'x'|| color[1][1] == 'X'))
    {
        j = 2;
        while (color[1][j])
        {
            if (!ft_isalnum(color[1][j]) || (i >= 8))
            {
                k = 0;
                while (color[k])
                {
                    free(color[k]);
                    k++;
                }
                free(color);
                return (0);
            }
            j++;
        }

        if (j <= 8)
            i = ft_atoi_base(color[1] + 2, HEX_BASE);
        else
            i = 0;
    }
    j = 0;
    while (color[j])
    {
        free(color[j]);
        j++;
    }
    free(color);
    return i;
}
*/

int ft_getcolor(const char *str)
{
    char **color;
    int color_value = 0; // Default color value is 0 (black)
    int i;

    // Split the string by ','
    color = ft_split(str, ',');
    if (!color)
    {
        fprintf(stderr, "Error: Could not allocate memory for color values\n");
        exit(1);
    }

    // Check if the color part exists and starts with '0x' or '0X'
    if (color[1] && color[1][0] == '0' && (color[1][1] == 'x' || color[1][1] == 'X'))
    {
        i = 2;
        // Validate the remaining characters after '0x'
        while (color[1][i])
        {
            if (!ft_isalnum(color[1][i]) || i >= 8) // Adjusted to allow shorter hex colors like 0xFFF
            {
                color_value = 0; // Invalid format, return 0 (default color)
                break;
            }
            i++;
        }
        // If valid, convert to an integer (hexadecimal base)
        if (i <= 8) // Allow shorter formats like 0xFFF or 0xFFFFFF
        {
            color_value = ft_atoi_base(color[1] + 2, HEX_BASE);
        }
    }

    // Free allocated memory
    i = 0;
    while (color[i])
    {
        free(color[i]);
        i++;
    }
    free(color);

    return color_value;
}
void color_mode(w_data *data)
{
    if (data->has_color)
        colorize(data);
    else
        colorize_gradient(data);
        //colorize(data);
}


void assign_info(w_data *data)
{
    int i;
    int j;
    char **split_line;

    i = 0;

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
            // check if the value is a number
            if (!ft_isdigit(split_line[j][0]) && split_line[j][0] != '-')
            {
                fprintf(stderr, "Error: Invalid character in file\n");
                // the data is :
                printf("data: %s\n in point[%d][%d]\n", split_line[j], i, j);
                exit(1);
                // if it is, set it to 0
                data->points[i][j].z = 0;
            }
            // assigning the z value to the points array
            data->points[i][j].z = ft_atoi(split_line[j]);
            data->points[i][j].color = ft_getcolor(split_line[j]);
            j++;
        }

        // free the split line
        j = 0;
        while (split_line[j])
        {
            free(split_line[j]);
            j++;
        }
        free(split_line);
        i++;
    }
}

// reads the file and assigns important values to the data struct
void read_fdf(w_data *data)
{
    int fd;

    // checking if the file is in the correct format
    // and opening the file

    if (!format_checker(data->file))
        exit(1);

    fd = open(data->file, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error: Could not open file %s\n", data->file);
        exit(1);
    }

    // counting the number of lines and columns in the file
    count_grid(fd, data);
    close(fd);

    // reopening the file to read the values
    fd = open(data->file, O_RDONLY);
    // making the points array
    data->points = make_points(data);
    // getting the Z and color values from the file
    data->z_values = info_parser(fd, data);
    
    // assigning the Z and color values to the points array
    assign_info(data);

    // printing the points coords and colors
    // print_data(data);

    // closing the file
    close(fd);
}

void find_min_max_z(w_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    data->min_z = data->points[0][0].z;
    data->max_z = data->points[0][0].z;

    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            if (data->points[i][j].z < data->min_z)
                data->min_z = data->points[i][j].z;
            if (data->points[i][j].z > data->max_z)
                data->max_z = data->points[i][j].z;
            j++;
        }
        i++;
    }
}
