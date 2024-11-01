#include "get_next_line.h"
#include <stdio.h>

size_t	get_line_len(int fd)
{
	char	char_buf[1];
	size_t	readbytes;

	readbytes = 0;
	while (*char_buf != '\n' && *char_buf != EOF)
	{
		readbytes += read(fd, char_buf, 1);
	}
	return (readbytes);
}

void	read_twice_to_get_linelen(int fd)
{
	char	line_buf[100];
	size_t	readbytes;

	readbytes = get_line_len(fd);
	read(fd, line_buf, readbytes);
	line_buf[readbytes] = 0;
	printf("line obtained: %s\n", line_buf);
}

void	read_and_print_1char(int fd)
{
	char	buf[100];
	char	temp[1];
	int		index = 0;
	
	while (*temp != '\n' && *temp != EOF)
	{
		read(fd, temp, 1);
		buf[index++] = *temp;
	}
	printf("buf: %s\n", buf);
	index = 0;
	while (*temp != '\n' && *temp != EOF)
	{
		read(fd, temp, 1);
		buf[index++] = *temp;
	}
	printf("buf after 2nd iteration: %s\n", buf);
}

void	read_and_print_longbuf(int fd)
{
	char	buf[20];
	
	read(fd, buf, 19);
	printf("buf: %s\n", buf);
}

// max files open at once: 1048576 (dk y)
// opening a file creates an entry in the open file table, which is shared by
// all processes, this is where the file position is stored and updated
// (incremented by the nbytes written return value of the open() func)
// 1 entry per opened file through open() func
//
// v-node table: other global data struct, os-level abstraction of ways to
// store files on a system (how big, what type, where stored, etc.)
// 1 entry per file (if a file is opened twice, still only one v-node entry)
//
// parent and child ? fork ? file pos is updated by either process and impacts
// both

int main()
{
	int		fd;
	
	fd = open("file.txt", O_RDONLY);
	
	/*
	read_twice_to_get_linelen(fd);
	read_twice_to_get_linelen(fd);
	*/
	read_and_print_1char(fd);
	read_and_print_1char(fd);
	read_and_print_longbuf(fd);
	read_and_print_longbuf(fd);
	
	return 0;
}
