/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:29:51 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/17 22:04:57 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strdup2(char *str, t_data *data)
{
	int	i;

	i = 0;
	data->len = 0;
	if (!data->newline)
	{
		*str = 0;
		return ;
	}
	data->j = -0;
	while (str[data->j] && str[data->j] != '\n')
		data->j++;
	while (str[data->len])
		data->len++;
	if (str[data->j] == '\n')
		str[data->j++] = 0; 
	while (str[data->j])
	{
		str[i++] = str[data->j];
		data->j++;
	}
	while (i < (int)data->j)
		str[i++] = 0;
}



// Append the buffer to the line
char	*append_buffer(t_data *data, char *buffer)
{
	size_t	i;
	char	*str;

	i = 0;
	data->j = 0;
	while (data->line && data->line[data->j])
		data->j++;
	data->len += data->j ;
	str = malloc(data->len + 1);
	if (!str)
		return (NULL);
	if (data ->line)
	{
		data->j = -1;
		while (data->line[++data->j])
			str[data->j] = data->line[data->j];
		free(data->line);
	}
	while (data->j < (int)data->len)
		str[data->j++] = buffer[i++];
	str[data->j] = '\0';
	ft_strdup2(buffer, data);
	return (str);
}

// Free all the memory allocated
void	clean_all(char *buffer, t_data *data)
{
	ft_strdup2(buffer, data);
	free(data->line);
}

size_t	grab_len(char *buffer, t_data *data)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		data->newline = 1;
	}
	return (i);
}

// Grab the line from the buffer
void	grab_line(char *buffer, t_data *data)
{
	data->len = grab_len(buffer, data);
	data->line = append_buffer(data, buffer);
}
