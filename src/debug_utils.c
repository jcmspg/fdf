/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:11 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/01 15:53:13 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	format_checker(const char *file)
{
	if (!file)
	{
		fprintf(stderr, "Error: No file specified\n");
		return (false);
	}
	if (ft_strncmp(file + ft_strlen(file) - 4, ".fdf", 4))
	{
		perror("Error: File is not .fdf format\n");
		return (false);
	}
	return (true);
}

// function to free any number of pointers
void	free_pointers(void *ptr, ...)
{
	va_list	args;
	void	*tmp;

	va_start(args, ptr);
	tmp = ptr;
	while (tmp)
	{
		free(tmp);
		tmp = va_arg(args, void *);
	}
	va_end(args);
}
