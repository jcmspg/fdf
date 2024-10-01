/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:53:59 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 17:18:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Data functions

// free lookup tables
void	free_lookup(t_w_data *data)
{
	if (data->lookup != NULL)
	{
		if (data->lookup->sin_table != NULL)
			free(data->lookup->sin_table);
		if (data->lookup->cos_table != NULL)
			free(data->lookup->cos_table);
		free(data->lookup);
	}
}

// free t_p
void	free_p(t_point **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	free_fp(t_f_point **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

// free all the p
void	free_all_p(t_w_data *data)
{
	if (data->p != NULL)
		free_p(data->p);
	if (data->p_b != NULL)
		free_fp(data->p_b);
	if (data->p_restore != NULL)
		free_fp(data->p_restore);
	if (data->i_p != NULL)
		free_fp(data->i_p);
}

void	free_data(t_w_data *data)
{
	free_all_p(data);
	if (data->grid != NULL)
		free(data->grid);
	if (data->img.img != NULL)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
