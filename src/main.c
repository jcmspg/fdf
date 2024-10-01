/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:36:42 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 21:05:42 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	f(t_w_data *data, char *c)
{
	data->grid->cols = 0;
	data->grid->rows = 0;
	data->file = c;
	data->title = "FDF";
}

void	init_main(t_w_data *data)
{
	init_data_w(data);
	create_window(data);
	create_image(data);
	read_fdf(data);
	intro_screen(data);
}

int	main(int argc, char **argv)
{
	t_w_data	window;

	if (argc != 2)
	{
		perror("Usage: ./fdf <filename>\n");
		return (1);
	}
	window.grid = (t_grid *)malloc(sizeof(t_grid));
	if (window.grid == NULL)
	{
		perror("Failed to allocate memory for grid\n");
		return (1);
	}
	f(&window, argv[1]);
	window.mlx = init_mlx();
	if (window.mlx == NULL)
	{
		perror("Failed to initialize mlx\n");
		return (1);
	}
	init_main(&window);
	mlx_key_hook(window.win, key_handle, &window);
	mlx_hook(window.win, 17, 0, close_window, &window);
	mlx_loop(window.mlx);
	return (0);
}
