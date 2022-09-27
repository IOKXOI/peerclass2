#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>
#include <fcntl.h>

int main()
{
	int fd1;
	char *str;
	fd1 = open("./files/41_with_nl", O_RDONLY);

	str = get_next_line(fd1);
	printf("FD1 = %s.", str);
	while (str)
	{
		free(str);
		str = get_next_line(fd1);
		if (str)
		{
			printf("FD1 = %s.", str);
			free(str);
		}
	}
	free(str);
	close(fd1);
	return (0);
}





