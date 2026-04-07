/**
 * low_open2.c
 *  - char buf[10], sizeof(buf) 설정
 *     . 마지막에 NULL 문자 저장 안됨(ARM에서는 strlen() 오류 발생)
 * - char buf[11], sizeof(buf)  설정
 *      . NULL 문자 추가됨
 *
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
    //char buf[10] = "Let's go!\n";
    char buf[11] = "Let's go!\n"; // NULL 문자 추가됨 

    fd = open("data1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        printf("open() error!");

    printf("strlen(buf): %zun", strlen(buf));
    printf("sizeof(buf): %zu\n", sizeof(buf));

    size = write(fd, buf, sizeof(buf));
    printf("write size: %d\n", size);

    close(fd);
    return 0;
}
