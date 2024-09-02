/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:57:54 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/03 19:15:19 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	t_data		data;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	data.line = NULL;
	data.newline = 0;
	while (!data.newline)
	{
		if (!*buffer[fd])
		{
			data.bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
			if (data.bytes_read > BUFFER_SIZE)
			{
				clean_all(buffer[fd], &data);
				return (NULL);
			}
			if (data.bytes_read == 0)
				return (data.line);
			buffer[fd][data.bytes_read] = 0;
		}
		grab_line(buffer[fd], &data);
	}
	return (data.line);
}
