#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	line_complete(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n' || *str == EOF)
			return (1);
		str++;
	}
	return (0);
}

t_buffer *new_node(void)
{
	t_buffer *node;

	node = (t_buffer *) malloc(sizeof(t_buffer));
	if (!node)
		return (NULL);
	node -> buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!node -> buffer)
	{
		free(node);
		return (NULL);
	}
	node -> next = NULL;
	return (node);
}

char	*concat(char *line, char *buffer)
{
	char	*new;
	int	i;

	new = (char *) malloc((ft_strlen(line) + BUFFER_SIZE + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	if (line)
	{
		while (line[i++])
			new[i] = line[i];
	}
	while (*buffer && *buffer != '\n' && *buffer != EOF)
	{
		new[i++] = *buffer;
		buffer++;
	}
	if (*buffer == '\n')
		new[i++] = '\n';
	new[i] = 0;
	free(line);
	return (new);
}

char	*trim(char *str)
{
	while (*str && *str != '\n' && *str != EOF)
		str++;
	if (*str == '\n')
		str++;
	return (str);
}

char	*gnl(int fd)
{
	static t_buffer	*node;
	char		*line;
	int		read_bytes;

	line = NULL;
	if (!node)
	{
		node = new_node();
		if (!node)
			return (NULL);
	}
	else
	{
		line = concat(line, node -> buffer);
		if (!line)
			return (NULL);
		node -> buffer = trim(node -> buffer);
	}
	if (line_complete(line))
		return (line);
	
	while (!line_complete(line))
	{
		node -> next = new_node();
		if (!node -> next)
			return (NULL);
		node = node -> next;
		read_bytes = read(fd, node -> buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		node -> buffer[read_bytes] = 0;
		line = concat(line, node -> buffer);
		if (!line)
			return (NULL);
	}
	node -> buffer = trim(node -> buffer);
	return (line);
}

int main()
{
	int fd;
	char *line;

	fd = open("file.txt", O_RDONLY);
	line = gnl(fd);
	printf("%s", line);
	close(fd);
	return 0;
}
