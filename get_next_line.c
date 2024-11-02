/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:16:44 by imeulema          #+#    #+#             */
/*   Updated: 2024/11/02 15:25:56 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char			*concat(char *line, char *buffer)
{
	char	*new;
	int		i;

	new = (char *) malloc((gnl_strlen(line) + BUFFER_SIZE + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	if (line)
	{
		while (line[i])
		{
			new[i] = line[i];
			i++;
		}
	}
	while (*buffer && *buffer != '\n')
		new[i++] = *(buffer++);
	if (*buffer == '\n')
		new[i++] = '\n';
	new[i] = 0;
	free(line);
	return (new);
}

int				line_complete(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char			*trim(char *str)
{
	char	*copy;
	int		i;
	int		j;

	copy = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i])
		copy[j++] = str[i++];
	copy[j] = 0;
	free(str);
	return (copy);
}

char			*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_bytes;

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
			return (NULL);
	}
	while (!line_complete(line))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		else if (read_bytes == 0)
		{
			free(buffer);
			break;
		}
		buffer[read_bytes] = 0;
		line = concat(line, buffer);
		if (!line)
			return (NULL);
	}
	if (read_bytes > 0)
		buffer = trim(buffer);
	return (line);
}
/*
int main()
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
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
