#include <stdlib.h>
#include <stdio.h>
#include "get_next_line_bonus.h"
#include <string.h>
#include <fcntl.h>




#ifndef FILE_1 
#define FILE_1 "./files/41_with_nl"
#endif

#ifndef FILE_2
#define FILE_2 "./files/alternate_line_nl_no_nl"
#endif

int main()
{
	int fd1;
	int fd2;
	char *str;
	fd1 = open(FILE_1, O_RDONLY);
	fd2 = open(FILE_2, O_RDONLY);

	str = get_next_line(fd1);
	printf("FD1 = %s", str);
	while (str)
	{
		str = free_this(&str);
		str = get_next_line(fd2);
		if (str)
		{
			printf("FD2 = %s", str);
			str = free_this(&str);
		}
		str = get_next_line(fd1);
		if (str)
		{
			printf("FD1 = %s", str);
			str = free_this(&str);
		}
	}
	str = free_this(&str);
	close(fd1);
	close(fd2);

	return 0;
}





