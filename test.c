#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void	read_and_print(int fd)
{
	char	buf[100];
	char	temp[1];
	int		index = 0;
	
	while (temp != '\n' || *temp != EOF)
	{
		read(fd, temp, 1);
		buf[index++] = *temp;
	}
	printf("%s", buf);

}

int main()
{
	int		fd;
	
	fd = open("file.txt", O_RDONLY);
	read_and_print(fd);
	read_and_print(fd);
	return 0;
}
