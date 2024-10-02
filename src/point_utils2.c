/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:24:36 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 20:26:23 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_backup_p(t_f_point **p, int i)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
}

static t_f_point	**allocate_p_grid(int lines, int cols)
{
	t_f_point	**p;
	int			i;

	p = (t_f_point **)ft_calloc(sizeof(t_f_point *), (lines + 1));
	if (!p)
	{
		perror("Error: Could not allocate memory for p\n");
		exit(1);
	}
	i = 0;
	while (i < lines)
	{
		p[i] = (t_f_point *)ft_calloc(sizeof(t_f_point), cols);
		if (!p[i])
		{
			perror("Error: Could not allocate memory for p[i]\n");
			free_backup_p(p, i - 1);
			exit(1);
		}
		i++;
	}
	p[lines] = NULL;
	return (p);
}

static void	copy_points(t_f_point **p, t_w_data *data, int lines, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < lines)
	{
		j = 0;
		while (j < cols)
		{
			p[i][j].x = data->p[i][j].x;
			p[i][j].y = data->p[i][j].y;
			p[i][j].z = data->p[i][j].z;
			p[i][j].color = data->p[i][j].color;
			j++;
		}
		i++;
	}
}

t_f_point	**backup_p(t_w_data *data)
{
	t_f_point	**p;
	int			lines;
	int			cols;

	lines = data->grid->rows;
	cols = data->grid->cols;
	p = allocate_p_grid(lines, cols);
	copy_points(p, data, lines, cols);
	return (p);
}
