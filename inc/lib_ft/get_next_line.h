/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:29:44 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/17 22:06:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_data
{
	size_t		bytes_read;
	size_t		len;
	size_t		full_len;
	char		*line;
	int			j;
	int			newline;
}	t_data;

char	*get_next_line(int fd);

// struct operations
void	clean_all(char *buffer, t_data *data);

// aux
void	ft_strdup2(char *str, t_data *data);
char	*append_buffer(t_data *data, char *buffer);
size_t	grab_len(char *buffer, t_data *data);
void	grab_line(char *buffer, t_data *data);

#endif
