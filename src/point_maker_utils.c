/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_maker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:31:10 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 18:36:23 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**allocate_point_array(int lines)
{
	t_point	**p;

	p = (t_point **)ft_calloc(sizeof(t_point *), (lines + 1));
	if (!p)
	{
		perror("Error: Could not allocate memory for p\n");
		exit(1);
	}
	return (p);
}

void	allocate_rows(t_point **p, int lines, int cols)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		p[i] = (t_point *)ft_calloc(sizeof(t_point), cols);
		if (!p[i])
		{
			perror("Error: Could not allocate memory for p\n");
			while (i >= 0)
			{
				free(p[i]);
				i--;
			}
			free(p);
			exit(1);
		}
		i++;
	}
}

void	fill_points(t_w_data *data, t_point **p)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->grid->rows)
	{
		j = 0;
		while (j < data->grid->cols)
		{
			p[i][j].x = (int)j * (pointcalc(data));
			p[i][j].y = (int)i * (pointcalc(data));
			p[i][j].z = 0;
			j++;
		}
		i++;
	}
}

t_point	**make_p(t_w_data *data)
{
	t_point	**p;
	int		lines;
	int		cols;

	cols = data->grid->cols;
	lines = data->grid->rows;
	p = allocate_point_array(lines);
	allocate_rows(p, lines, cols);
	fill_points(data, p);
	data->grid->half_x = (data->window_w / 2) - (p[0][cols - 1].x / 2);
	data->grid->half_y = (data->window_h / 2) - (p[lines - 1][0].y / 2);
	return (p);
}
