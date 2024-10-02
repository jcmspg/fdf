/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:46:47 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 19:59:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**split_color(const char *str)
{
	char	**color;

	color = ft_split(str, ',');
	if (!color)
	{
		perror("Error: Could not allocate memory for color\n");
		exit(1);
	}
	return (color);
}

static int	is_valid_hex_format(char *color)
{
	return (color && color[0] == '0' && (color[1] == 'x' || color[1] == 'X'));
}

static int	validate_and_convert_color(char *color)
{
	int	i;

	i = 2;
	while (color[i])
	{
		if (!ft_isalnum(color[i]) || i >= 8)
			return (0);
		i++;
	}
	if (i <= 8)
		return (ft_atoi_base(color + 2, HEX_BASE));
	return (0);
}

static void	free_color(char **color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		free(color[i]);
		i++;
	}
	free(color);
}

int	ft_getcolor(const char *str)
{
	char	**color;
	int		color_value;

	color = split_color(str);
	if (is_valid_hex_format(color[1]))
		color_value = validate_and_convert_color(color[1]);
	else
		color_value = 0;
	free_color(color);
	return (color_value);
}
