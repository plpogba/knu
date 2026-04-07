/**
 * low_open4.c
 *  - char buf[100]으로 크기를 지정하고, strlen(buf) 크기만큼 파일로 저장
 *  - 배열의 크기만큼 파일에 저장됨, 문자열 길이 이후에는 NULL 문자로 채워짐
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

    //size = write(fd, buf, strlen(buf));
    size = write(fd, buf, strlen(buf)+1); // NULL값 저장
    printf("write size: %d\n", size);

    close(fd);
    return 0;
}
