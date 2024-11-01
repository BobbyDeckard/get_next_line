#include "get_next_line.h"
#include <stdio.h>

int		line_completed(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n' || *buffer == EOF)
			return (1);
		buffer++;
	}
	return (0);
}

char	*gnl_proto(int fd)
{
	static t_buffer	*list;
	t_buffer		*link;
	int				iterations;
	int				line_index;
	int				buffer_index;
	size_t			read_bytes;
	char			*line;

	if (!list)
	{
		list = (t_buffer *) malloc(sizeof(t_buffer));
		if (!list)
			return (NULL);
	}
	link = list;
	link -> next = NULL;
	link -> buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(link -> buffer))
		return (NULL);
	read_bytes = read(fd, link -> buffer, BUFFER_SIZE);
	link -> buffer[read_bytes] = 0;
	iterations = 1;
	while (!line_completed(link -> buffer))
	{
		link -> next = (t_buffer *) malloc(sizeof(t_buffer));
		if (!(link -> next))
				return (NULL);
		link = link -> next;
		link -> next = NULL;
		link -> buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!link -> buffer)
			return (NULL);
		read_bytes = read(fd, link -> buffer, BUFFER_SIZE);
		link -> buffer[read_bytes] = 0;
		iterations++;
	}
	line = (char *) malloc((iterations * BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	link = list;
	line_index = 0;
	while (!line_completed(link -> buffer))
	{
		buffer_index = 0;
		while (link -> buffer[buffer_index])
			line[line_index++] = link -> buffer[buffer_index++];
		link = link -> next;
	}
	buffer_index = 0;
	while (link -> buffer[buffer_index] != '\n' && link -> buffer[buffer_index] != EOF)
		line[line_index++] = link -> buffer[buffer_index++];
	line[line_index] = 0;
	return (line);
}

int main()
{
	int fd;
	char *result;

	fd = open("file.txt", O_RDONLY);
	result = gnl_proto(fd);
	printf("%s\n", result);
	free(result);
	result = gnl_proto(fd);
	printf("%s\n", result);
	free(result);
	return 0;
}
