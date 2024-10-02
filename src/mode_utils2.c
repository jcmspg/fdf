/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:42:49 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 16:58:17 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_mode(int key, t_w_data *data)
{
	if (key == SPACE && !data->mode)
		start_iso(data);
	else if (key == H)
		display_help(key, data);
	else if (key == I && data->mode != 'i')
		switch_to_iso(data);
	else if (key == G)
		switch_to_globe(data);
	else if (key == N)
		switch_to_conic(data);
	else if (key == ESC)
		close_window(data);
	else if (key == F)
		reset(data);
	else if (key == C)
		color(key, data);
}

void	handle_interaction(int key, t_w_data *data)
{
	if (key == P)
		data->interaction = 'p';
	if (key == R && data->mode != 'g')
		data->interaction = 'r';
	if (key == Z)
		data->interaction = 'z';
	if (key == O && data->mode == 'g')
		data->interaction = 'o';
}

void	interaction_functions(int key, t_w_data *data)
{
	if (key == W || key == S || key == A || key == D || key == Q || key == E)
	{
		if (data->interaction == 'p')
			pan(key, data);
		if (data->interaction == 'r')
			rotate(key, data);
		if (data->interaction == 'z')
			zoom_in_out(key, data);
		if (data->interaction == 'o' && data->mode == 'g')
			ro_sphere(key, data);
		if (data->interaction == 'o' && data->mode == 'c')
			change_focus(key, data);
	}
}

int	key_handle(int key, t_w_data *data)
{
	if (key == N || key == I || key == C || key == G
		|| key == ESC || key == F || key == SPACE || key == H)
		change_mode(key, data);
	if (key == P || key == O || key == Z || key == R)
		handle_interaction(key, data);
	if (key == W || key == S || key == A || key == D || key == Q || key == E)
		interaction_functions(key, data);
	return (0);
}
