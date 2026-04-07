#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100

void error_handling(char *message);

int main(void)
{
	int fd;
	int str_len = 0;
	char buf[BUF_SIZE] = {0};
	int read_len = 0;
	int index = 0;

	fd = open("data1.txt", O_RDONLY);
	if (fd == -1)
		error_handling("open() error!");
	
	while((read_len=read(fd, &buf[index++], 1)) != 0)
	{
		if (str_len == -1)
			error_handling("read() error!");

		str_len += read_len;
	}
	printf("read size: %d\n", str_len);
	printf("file data: %s", buf);

	close(fd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}