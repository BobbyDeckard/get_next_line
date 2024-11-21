/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:16:44 by imeulema          #+#    #+#             */
/*   Updated: 2024/11/21 12:01:23 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat(char *line, char *buffer)
{
	char	*new;
	int		i;

	new = (char *) malloc((gnl_strlen(line) + BUFFER_SIZE + 1) * sizeof(char));
	if (!new)
		return (free_null(line));
	i = 0;
	while (line && line[i])
	{
		new[i] = line[i];
		i++;
	}
	while (*buffer && *buffer != '\n')
		new[i++] = *(buffer++);
	if (*buffer == '\n')
		new[i++] = '\n';
	new[i] = 0;
	free(line);
	return (new);
}

char	*trim(char **buffer)
{
	char	*copy;
	int		i;
	int		j;

	copy = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!copy)
		return (free_null(*buffer));
	i = 0;
	j = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	while ((*buffer)[i])
		copy[j++] = (*buffer)[i++];
	if (j == 0)
		copy = free_null(copy);
	else
		copy[j] = 0;
	*buffer = free_null(*buffer);
	return (copy);
}

char	*make_line(char **line, int *read_bytes, int fd, char **buffer)
{
	while (!line_complete(*line))
	{
		*read_bytes = read(fd, *buffer, BUFFER_SIZE);
		if (*read_bytes == -1)
		{
			*buffer = free_null(*buffer);
			return (free_null(*line));
		}
		else if (*read_bytes == 0)
		{
			*buffer = free_null(*buffer);
			break ;
		}
		else
			(*buffer)[*read_bytes] = 0;
		*line = concat(*line, *buffer);
		if (!*line)
			return (free_null(*buffer));
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (!buffer)
	{
		buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
	}
	else
	{
		line = concat(line, buffer);
		if (!line)
			return (free_null(buffer));
	}
	line = make_line(&line, &read_bytes, fd, &buffer);
	if (buffer)
		buffer = trim(&buffer);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int		fd;
	char	*line;

	fd = open("read_error.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return 0;
}
*/
