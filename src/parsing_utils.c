/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:24 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 22:31:55 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*read_line_or_exit(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		perror("Error: Could not read line from file\n");
		exit(1);
	}
	return (line);
}

static int	count_columns(char *line)
{
	char	**tmp;
	int		num_cols;

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
	free(tmp);
	return (num_cols);
}

static void	process_line(int *num_cols, int *num_lines, char *line)
{
	if (*num_cols == -1)
		*num_cols = count_columns(line);
	free(line);
	(*num_lines)++;
}

static void	count_grid(int fd, t_w_data *data)
{
	char	*line;
	int		num_lines;
	int		num_cols;

	num_lines = 0;
	num_cols = -1;
	line = read_line_or_exit(fd);
	while (line != NULL)
	{
		process_line(&num_cols, &num_lines, line);
		line = get_next_line(fd);
	}
	data->grid->cols = num_cols;
	data->grid->rows = num_lines;
}

void	read_fdf(t_w_data *data)
{
	int	fd;

	if (!format_checker(data->file))
		exit(1);
	fd = open(data->file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Could not open file\n");
		exit(1);
	}
	count_grid(fd, data);
	close(fd);
	fd = open(data->file, O_RDONLY);
	data->p = make_p(data);
	data->z_values = info_parser(fd, data);
	assign_info(data);
	find_min_max_z(data);
	data->i_p = backup_p(data);
	close(fd);
}
