/**
 * low_open3.c
 *  - char buf[100]에서 크기를 지정하고, sizeof(buf) 크기만큼 파일로 저장
 *  - NULL로 채워져서 100 bytes 저장됨
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd;
    int size;
    char buf[100] = "Let's go!\n";

    fd = open("data1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        printf("open() error!");

    printf("strlen(buf): %zu\n", strlen(buf));
    printf("sizeof(buf): %zu\n", sizeof(buf));

    size = write(fd, buf, sizeof(buf));
    printf("write size: %d\n", size);

    close(fd);
    return 0;
}
