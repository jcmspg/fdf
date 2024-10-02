/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:50:45 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 17:16:28 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start_iso(t_w_data *data)
{
	data->mode = 'i';
	backup_data(data);
	clear_image(data);
	build_model(data);
	change_backup(data);
	make_image(data);
	draw_gui(data);
}

void	switch_to_iso(t_w_data *data)
{
	data->mode = 'i';
	clear_image(data);
	build_model(data);
	change_backup(data);
	make_image(data);
	draw_gui(data);
}

void	switch_to_globe(t_w_data *data)
{
	data->mode = 'g';
	build_sphere(data);
	draw_gui(data);
}

void	switch_to_conic(t_w_data *data)
{
	data->mode = 'c';
	build_conic(data);
	draw_gui(data);
}
