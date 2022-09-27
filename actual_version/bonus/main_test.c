#include <stdlib.h>
#include <stdio.h>
#include "get_next_line_bonus.h"
#include <string.h>
#include <fcntl.h>

int main()
{
	int i = 1;
	int fd1;
	int fd2;
	int fd3;
	char *str;
	fd1 = open("./files/41_with_nl", O_RDONLY);
	fd2 = open("./files/42_with_nl", O_RDONLY);
	fd3 = open("./files/43_with_nl", O_RDONLY);
while (i < 3)
{
	str = get_next_line(fd1);
	printf("FD1 = %s", str);
	free(str);
	str = get_next_line(fd2);
	if (str)
	{
		printf("FD2 = %s", str);
		free(str);
	}
	str = get_next_line(fd3);
	if (str)
	{
		printf("FD3 = %s", str);
		free(str);
	}
	printf("Appel = %d termine \n", i );
	printf("\n\n\n\n\n");
	str = get_next_line(1003);
	if (str)
	{
		printf("PAS FD DU TOUT = %s", str);
		free(str);
	}
	i++;
	
}
//	close(fd1);
//	close(fd2);

	close(fd1);
	return 0;
}





