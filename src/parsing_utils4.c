/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:12:39 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 20:20:01 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_split_line(char **split_line)
{
	int	j;

	j = 0;
	while (split_line[j])
	{
		free(split_line[j]);
		j++;
	}
	free(split_line);
}

static void	assign_point_info(t_w_data *data, char **split_line, int i, int j)
{
	if (split_line[j] == NULL)
	{
		perror("Error: Invalid number of columns in file\n");
		exit(1);
	}
	if (!ft_isdigit(split_line[j][0]) && split_line[j][0] != '-')
	{
		perror("Error: Invalid character in file\n");
		exit(1);
	}
	data->p[i][j].z = ft_atoi(split_line[j]);
	if (data->has_color)
		data->p[i][j].color = ft_getcolor(split_line[j]);
}

static void	parse_row(t_w_data *data, int i)
{
	char	**split_line;
	int		j;

	split_line = ft_split(data->z_values[i], ' ');
	if (!split_line)
	{
		perror("Error: Could not allocate memory for split_line\n");
		exit(1);
	}
	j = 0;
	while (j < data->grid->cols)
	{
		assign_point_info(data, split_line, i, j);
		j++;
	}
	free_split_line(split_line);
}

static void	free_z_values(t_w_data *data)
{
	int	i;

	i = 0;
	while (i < data->grid->rows)
	{
		free(data->z_values[i]);
		i++;
	}
	free(data->z_values);
}

void	assign_info(t_w_data *data)
{
	int	i;

	i = 0;
	while (i < data->grid->rows)
	{
		parse_row(data, i);
		i++;
	}
	free_z_values(data);
}
