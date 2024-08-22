/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:41:21 by malourei          #+#    #+#             */
/*   Updated: 2024/05/21 17:52:07 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_stack(char *stack)
{
	int	i;
	int	j;
	int	n;

	if (!*stack)
		return ;
	i = 0;
	n = 0;
	j = ft_strlen(stack);
	while (stack[n] && stack[n] != '\n')
		n++;
	if (n == j)
	{
		*stack = 0;
		return ;
	}
	stack[n] = 0;
	n++;
	while (n < j)
	{
		stack[i] = stack[n];
		n++;
		i++;
	}
	stack[i] = 0;
}

static char	*read_line(char stack[], char *line, char *n)
{
	int		j;
	char	*str;

	j = 0;
	while (stack[j] && stack[j] != '\n')
		j++;
	if (stack[j++] == '\n')
		*n = '1';
	str = malloc(sizeof(char) * (j + ft_strlen(line) + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, line);
	if (line)
		free(line);
	ft_strncat(str, stack, j);
	free_stack(stack);
	return (str);
}

static char	*ft_check_erro(char *stack, int i, char *line)
{
	if (i < 0)
	{
		if (*stack)
			*stack = 0;
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stack[FD_MAX][BUFFER_SIZE + 1];
	char		*line;
	char		n;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	i = 0;
	line = NULL;
	n = 0;
	while (!n)
	{
		if (!*stack[fd])
		{
			i = read(fd, stack[fd], BUFFER_SIZE);
			if (i <= 0)
				return (ft_check_erro(stack[fd], i, line));
			stack[fd][i] = 0;
		}
		line = read_line(stack[fd], line, &n);
		if (!line)
			return (NULL);
	}
	return (line);
}
