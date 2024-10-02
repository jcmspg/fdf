/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:48:07 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 20:17:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_color(const char *line, t_w_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
		{
			data->has_color = 1;
			return ;
		}
		i++;
	}
	data->has_color = 0;
	data->color_mode = 0;
}

void	color_mode(t_w_data *data)
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

static char	**z_maker(t_w_data *data)
{
	char	**z_values;

	z_values = ft_calloc(data->grid->rows, sizeof(char *));
	if (!z_values)
	{
		perror("Error: Could not allocate memory for z_values\n");
		exit(1);
	}
	return (z_values);
}

char	**info_parser(int fd, t_w_data *data)
{
	char	**z_values;
	char	*line;

	z_values = z_maker(data);
	data->i = 0;
	while (data->i < data->grid->rows)
	{
		line = get_next_line(fd);
		if (!line)
		{
			perror("Error: Could not read line from file\n");
			exit(1);
		}
		check_color(line, data);
		z_values[data->i] = ft_strdup(line);
		if (!z_values[data->i])
		{
			perror("Error: Could not allocate memory for z_values[i]\n");
			free(line);
			exit(1);
		}
		free(line);
		data->i++;
	}
	return (z_values);
}

void	find_min_max_z(t_w_data *data)
{
	int	i;
	int	j;

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
