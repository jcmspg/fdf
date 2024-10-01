/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:24 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void count_grid(int fd, t_w_data *data)
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
                perror("Error: Could not allocate memory for tmp\n");
                exit(1);
            }
            num_cols = 0;
            while (tmp[num_cols])
            {
                free(tmp[num_cols]);
                num_cols++;
            }
			//draw_poly(data);
            free(tmp);
        }
        free(line);
        num_lines++;
        line = get_next_line(fd);
    }
    data->grid->cols = num_cols;
    data->grid->rows = num_lines;
}



// check if theres any color info in the file. If there is, t_w_data->has_color =1
// if not, t_w_data->has_color = 0
void check_color(const char *line, t_w_data *data)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == ',')
        {
            data->has_color = 1;
            return;
        }
        i++;
    }
    data->has_color = 0;
    data->color_mode = 0;
}

char **info_parser(int fd, t_w_data *data)
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

// Get the color value from the string
int ft_getcolor(const char *str)
{
    char **color;
    //default color is white
    int color_value = 0xFFFFFF;
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

void color_mode(t_w_data *data)
{
    if (data->has_color)
        data->color_mode = 0;

    if (data->color_mode == 0)
        colorize(data);
    else if (data->color_mode == 1)
        colorize_grayscale(data);
    else if (data->color_mode == 2)
        colorize_gradient(data);

}


void assign_info(t_w_data *data)
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
            // Validate split_line[j] before accessing it
            if (split_line[j] == NULL)
            {
                fprintf(stderr, "Error: split_line[%d] is NULL\n", j);
                exit(1);
            }

            // Check if the value is a valid number
            if (!ft_isdigit(split_line[j][0]) && split_line[j][0] != '-')
            {
                fprintf(stderr, "Error: Invalid character in file\n");
                printf("data: %s\n in point[%d][%d]\n", split_line[j], i, j);
                exit(1);
            }

            // Assigning the z value to the p array
			// make sure values are normalized to fit the window proportionally to the grid
            data->p[i][j].z = ft_atoi(split_line[j]);
            // if the file has color info, we assign the color to the p
            if (data->has_color)
                data->p[i][j].color = ft_getcolor(split_line[j]);
            j++;
        }

        // Free the split line
        j = 0;
        while (split_line[j])
        {
            free(split_line[j]);
            j++;
        }
        free(split_line);
        i++;
    }

    // Free z_values
    i = 0;
    while (i < data->grid->rows)
    {
        free(data->z_values[i]);
        i++;
    }
    free(data->z_values);
}

void find_min_max_z(t_w_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    data->min_z = data->p[0][0].z;
    data->max_z = data->p[0][0].z;

    while (i < data->grid->rows)
    {
        j = 0;
        while (j < data->grid->cols)
        {
            if (data->p[i][j].z < data->min_z)
                data->min_z = data->p[i][j].z;
            if (data->p[i][j].z > data->max_z)
                data->max_z = data->p[i][j].z;
            j++;
        }
        i++;
    }
}


// reads the file and assigns important values to the data struct
void read_fdf(t_w_data *data)
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
    // making the p array
    data->p = make_p(data);
    // getting the Z and color values from the file
    data->z_values = info_parser(fd, data);
	//print scale
	printf("scale: %f\n", data->scale);


    // assigning the Z and color values to the p array
    assign_info(data);
    find_min_max_z(data);

	//backing up the p for iso
	data->i_p = backup_p(data);


	//create backup p values

	// printing the p coords and colors
    // print_data(data);


    // closing the file
    close(fd);
}

