#include "get_next_line.h"
#include <stdio.h>

t_buffer	*new_node(t_buffer *node)
{
	node = (t_buffer *) malloc(sizeof(t_buffer));
	if (!node)
		return (NULL);
	node -> buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!node -> buffer)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

char	*recover_last_buffer(char *buffer, int iterations)
{

}

int main()
{
	static t_static	*tracking;
	t_buffer	*fnode; // first node
	t_buffer	*cnode; // current node

	if (!tracking)
	{
		tracking = new_node();
		if (!tracking)
			return (NULL);
		tracking -> iterations = 1;
		tracking -> buffer = NULL;
	}

	fnode = new_node();
	if (!fnode) // free tracking ?
		    // can maybe make a func that frees a whole list and that could work on both t_buffer and t_static
		return (NULL);
	cnode = fnode;

	char		*line; // problem: we should know beforehand what size to allocate for line
			       // case 1: we iterate through the read function and allocate buffersize * iterations + 1 (basecase)
			       // case 2: the function's last call gave us a truncated buffer to start with, we should now know
			       // 	  wether or not:
			       // 	  1) the full line is already present in the last call's buffer
			       // 	  2) if not, how many more iterations are necessary to get to the end of the line
			       // that means we need to read first..? rather go through the last buffer and check what we find there ?

	if (tracking -> buffer)
	{
		
		while (tracking -> buffer[str_index++] && iter_count < tracking -> iterations)
		{
			if (tracking -> buffer[str_index] == '\n' && iter_count + 1 == tracking -> iterations)
				while (tracking -> buffer[str_index] && tracking -> buffer[str_index != '\n' || tracking -> buffer[str_index] != EOF)
					fnode -> buffer[cpy_index++] = tracking -> buffer[str_index++];
				
		}
	}


}
